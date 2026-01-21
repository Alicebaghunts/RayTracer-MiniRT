/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:06:58 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/21 10:12:53 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	destroy_app(t_mlx *app)
{
	if (!app)
		return ;
	if (app->img && app->mlx)
		mlx_destroy_image(app->mlx, app->img);
	if (app->window && app->mlx)
		mlx_destroy_window(app->mlx, app->window);
	if (app->mlx)
		free(app->mlx);
	free(app);
}

static void	destroy_tex(void *mlx, t_texture *tex)
{
	if (tex && tex->img)
		mlx_destroy_image(mlx, tex->img);
}

static void	destroy_obj_images(void *mlx, t_object *obj)
{
	if (!obj || !obj->data)
		return ;
	if (obj->type == 's' && obj->data->sphere)
	{
		destroy_tex(mlx, obj->data->sphere->texture);
		destroy_tex(mlx, obj->data->sphere->bump);
	}
	else if (obj->type == 'p' && obj->data->plane)
		destroy_tex(mlx, obj->data->plane->texture);
	else if (obj->type == 'c' && obj->data->cylinder)
	{
		destroy_tex(mlx, obj->data->cylinder->texture);
		destroy_tex(mlx, obj->data->cylinder->bump);
	}
	else if (obj->type == 'o' && obj->data->cone)
		destroy_tex(mlx, obj->data->cone->texture);
}

void	destroy_scene_images(t_mlx *app)
{
	t_list		*node;
	t_object	*obj;

	if (!app || !app->scene || !app->scene->objects || !app->mlx)
		return ;
	node = app->scene->objects;
	while (node)
	{
		obj = (t_object *)node->content;
		destroy_obj_images(app->mlx, obj);
		node = node->next;
	}
}
