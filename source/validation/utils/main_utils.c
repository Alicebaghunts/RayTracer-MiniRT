/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 17:56:26 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/16 20:29:54 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	destroy_app(t_mlx *app)
{
	if (!app)
		return ;
	if (app->window && app->mlx)
		mlx_destroy_window(app->mlx, app->window);
	if (app->scene)
		free_scene(app->scene);
	if (app->mlx)
		free(app->mlx);
	free(app);
}

int	close_window(t_mlx *app)
{
	destroy_app(app);
	exit(0);
	return (0);
}

void	switch_camera(t_mlx *app)
{
	t_list	*cur;

	if (!app || !app->scene || !app->scene->camera)
		return ;
	cur = app->scene->active_camera;
	if (!cur)
		cur = app->scene->camera;
	else if (cur->next)
		cur = cur->next;
	else
		cur = app->scene->camera;
	app->scene->active_camera = cur;
	mlx_clear_window(app->mlx, app->window);
	drawing(app);
}

t_object	*get_object_at_pixel(t_mlx *app, int x, int y)
{
	t_camera	*cam;
	t_list		*cam_node;
	t_vector	ray_dir;
	double		min_t;
	t_object	*closest;

	if (!app || !app->scene)
		return (NULL);
	cam_node = app->scene->active_camera;
	if (!cam_node)
		cam_node = app->scene->camera;
	if (!cam_node)
		return (NULL);
	cam = (t_camera *)cam_node->content;
	ray_dir = compute_ray(cam, x, y);
	closest = find_closest_object(app->scene, cam, ray_dir, &min_t);
	return (closest);
}

void	cycle_render_mode(t_mlx *app, t_object *obj)
{
	if (!app || !app->scene || !obj)
		return ;
	if (app->scene->selected_object == obj)
	{
		if (app->scene->selected_mode == MODE_TEXTURE)
			app->scene->selected_mode = MODE_CHECKERBOARD;
		else if (app->scene->selected_mode == MODE_CHECKERBOARD)
			app->scene->selected_mode = MODE_BUMP;
		else
			app->scene->selected_mode = MODE_TEXTURE;
	}
	else
	{
		app->scene->selected_object = obj;
		app->scene->selected_mode = MODE_TEXTURE;
	}
	mlx_clear_window(app->mlx, app->window);
	drawing(app);
}
