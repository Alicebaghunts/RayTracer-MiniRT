/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 23:40:49 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/22 21:34:50 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->ambient)
	{
		if (scene->ambient->color)
			free(scene->ambient->color);
		free(scene->ambient);
	}
	ft_lstclear(&scene->camera, free_camera);
	ft_lstclear(&scene->lights, free_light);
	ft_lstclear(&scene->objects, free_object);
	free(scene);
}

void	free_scene_inits(t_scene *scene, char **line, char **map)
{
	if (scene)
		free_scene(scene);
	if (line)
		ft_free_matrix(line);
	if (map)
		ft_free_matrix(map);
}

void	free_camera(void *content)
{
	t_camera	*camera;

	camera = (t_camera *)content;
	if (!camera)
		return ;
	if (camera->position)
		free(camera->position);
	if (camera->direction)
		free(camera->direction);
	free(camera);
}

void	free_object(void *content)
{
	t_object	*object;

	object = (t_object *)content;
	if (!object)
		return ;
	if (object->data)
	{
		if (object->type == 'c')
			free_cylinder(object->data->cylinder);
		else if (object->type == 's')
			free_sphere(object->data->sphere);
		else if (object->type == 'p')
			free_plane(object->data->plane);
		else if (object->type == 'o')
			free_cone(object->data->cone);
		free(object->data);
	}
	free(object);
}
