/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:38:05 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 10:49:13 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	render_pixel_to_app(t_mlx *app, t_camera *cam, int x, int y)
{
	t_vector	rd;
	t_hit		hit;
	t_color		sh;
	int			color;

	rd = compute_ray(cam, x, y);
	hit.closest = find_closest_object(app->scene, cam, rd, &hit.min_t);
	if (hit.closest)
	{
		hit.hit_point = vector_addition(*cam->position, vector_scale(rd,
					hit.min_t));
		hit.normal = get_normal(hit.closest, hit.hit_point);
		hit.normal = normalize(hit.normal);
		if (vector_dot(rd, hit.normal) > 0.0)
			hit.normal = vector_scale(hit.normal, -1.0);
		sh = shade(app->scene, hit.hit_point, hit.normal, hit.closest);
		color = (sh.red << 16) | (sh.green << 8) | sh.blue;
		my_mlx_pixel_put(app, x, y, color);
	}
	else
		my_mlx_pixel_put(app, x, y, 0x000000);
}

static void	*thread_draw(void *arg)
{
	t_draw_args	*a;
	int			y;
	int			x;

	a = (t_draw_args *)arg;
	if (!a)
		return (NULL);
	y = a->y_start;
	while (y < a->y_end)
	{
		x = 0;
		while (x < MLX_X)
		{
			render_pixel_to_app(a->app, a->cam, x, y);
			x++;
		}
		y++;
	}
	free(a);
	return (NULL);
}

static void	wait_for_threads_and_put(pthread_t threads[], t_mlx *app)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(app->mlx, app->window, app->img, 0, 0);
}

static int	launch_thread(pthread_t threads[], int idx, t_mlx *app,
		t_camera *cam)
{
	t_draw_args	*args;

	args = malloc(sizeof(*args));
	if (!args)
		return (-1);
	args->app = app;
	args->cam = cam;
	args->y_start = idx * (MLX_Y / THREADS);
	if (idx == THREADS - 1)
		args->y_end = MLX_Y;
	else
		args->y_end = args->y_start + (MLX_Y / THREADS);
	if (pthread_create(&threads[idx], NULL, thread_draw, args) != 0)
	{
		free(args);
		return (-1);
	}
	return (0);
}

int	start_render_threads(t_mlx *app)
{
	pthread_t	threads[THREADS];
	t_camera	*cam;
	int			i;

	cam = get_active_camera(app);
	if (!cam)
		return (-1);
	i = 0;
	while (i < THREADS)
	{
		if (launch_thread(threads, i, app, cam) != 0)
		{
			cleanup_and_fallback(threads, i, app, cam);
			return (0);
		}
		i++;
	}
	wait_for_threads_and_put(threads, app);
	return (0);
}
