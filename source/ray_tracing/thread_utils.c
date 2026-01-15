/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <generated>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:30:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/15 18:30:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include <pthread.h>
#include <stdlib.h>

#ifndef THREADS
# define THREADS 8
#endif

typedef struct s_draw_args
{
	t_mlx		*app;
	t_camera	*cam;
	int		y_start;
	int		y_end;
}t_draw_args;

static void *thread_draw(void *arg)
{
	t_draw_args *a = (t_draw_args *)arg;
	int x; int y;
	t_vector rd; t_hit hit; t_color sh;
	if (!a) return (NULL);
	y = a->y_start;
	while (y < a->y_end)
	{
		x = 0;
		while (x < MLX_X)
		{
			rd = compute_ray(a->cam, x, y);
			hit.closest = find_closest_object(a->app->scene, a->cam, rd, &hit.min_t);
			if (hit.closest)
			{
				hit.hit_point = vector_addition(*a->cam->position, vector_scale(rd, hit.min_t));
				hit.normal = get_normal(hit.closest, hit.hit_point);
				hit.normal = normalize(hit.normal);
				if (vector_dot(rd, hit.normal) > 0.0)
					hit.normal = vector_scale(hit.normal, -1.0);
				sh = shade(a->app->scene, hit.hit_point, hit.normal, hit.closest);
				my_mlx_pixel_put(a->app, x, y, (sh.red << 16) | (sh.green << 8) | sh.blue);
			}
			else
				my_mlx_pixel_put(a->app, x, y, 0x000000);
			x++;
		}
		y++;
	}
	free(a);
	return (NULL);
}

static void render_single(t_mlx *app, t_camera *cam)
{
	int x; int y; t_vector rd; t_hit hit; t_color sh;
	y = 0;
	while (y < MLX_Y)
	{
		x = 0;
		while (x < MLX_X)
		{
			rd = compute_ray(cam, x, y);
			hit.closest = find_closest_object(app->scene, cam, rd, &hit.min_t);
			if (hit.closest)
			{
				hit.hit_point = vector_addition(*cam->position, vector_scale(rd, hit.min_t));
				hit.normal = get_normal(hit.closest, hit.hit_point);
				hit.normal = normalize(hit.normal);
				if (vector_dot(rd, hit.normal) > 0.0)
					hit.normal = vector_scale(hit.normal, -1.0);
				sh = shade(app->scene, hit.hit_point, hit.normal, hit.closest);
				my_mlx_pixel_put(app, x, y, (sh.red << 16) | (sh.green << 8) | sh.blue);
			}
			else
				my_mlx_pixel_put(app, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int start_render_threads(t_mlx *app)
{
	pthread_t threads[THREADS];
	int i; t_draw_args *args; t_list *cn; t_camera *cam;
	if (!app || !app->scene) return (-1);
	cn = app->scene->active_camera ? app->scene->active_camera : app->scene->camera;
	if (!cn) return (-1);
	cam = (t_camera *)cn->content;
	i = 0;
	while (i < THREADS)
	{
		args = malloc(sizeof(*args));
		if (!args)
		{
			int j = 0;
			while (j < i) { pthread_join(threads[j], NULL); j++; }
			render_single(app, cam);
			mlx_put_image_to_window(app->mlx, app->window, app->img, 0, 0);
			return (0);
		}
		args->app = app; args->cam = cam;
		args->y_start = i * (MLX_Y / THREADS);
		if (i == THREADS - 1) args->y_end = MLX_Y; else args->y_end = args->y_start + (MLX_Y / THREADS);
		if (pthread_create(&threads[i], NULL, thread_draw, args) != 0)
		{
			free(args);
			int j = 0;
			while (j < i) { pthread_join(threads[j], NULL); j++; }
			render_single(app, cam);
			mlx_put_image_to_window(app->mlx, app->window, app->img, 0, 0);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < THREADS) { pthread_join(threads[i], NULL); i++; }
	mlx_put_image_to_window(app->mlx, app->window, app->img, 0, 0);
	return (0);
}
