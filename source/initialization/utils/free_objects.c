/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:31:40 by alisharu          #+#    #+#             */
/*   Updated: 2025/11/22 18:16:25 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

void	free_sphere(t_sphere *sphere)
{
	if (!sphere)
		return ;
	if (sphere->position)
		free(sphere->position);
	if (sphere->color)
		free(sphere->color);
	if (sphere->texture)
	{
		if (sphere->texture->path)
			free(sphere->texture->path);
		free(sphere->texture);
	}
	if (sphere->bump)
	{
		if (sphere->bump->path)
			free(sphere->bump->path);
		free(sphere->bump);
	}
	free(sphere);
}

void	free_plane(t_plane *plane)
{
	if (!plane)
		return ;
	if (plane->position)
		free(plane->position);
	if (plane->normal)
		free(plane->normal);
	if (plane->color)
		free(plane->color);
	if (plane->texture)
	{
		if (plane->texture->path)
			free(plane->texture->path);
		free(plane->texture);
	}
	free(plane);
}

void	free_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	if (cylinder->position)
		free(cylinder->position);
	if (cylinder->direction)
		free(cylinder->direction);
	if (cylinder->color)
		free(cylinder->color);
	if (cylinder->texture)
	{
		if (cylinder->texture->path)
			free(cylinder->texture->path);
		free(cylinder->texture);
	}
	free(cylinder);
}

void	free_cone(t_cone *cone)
{
	if (!cone)
		return ;
	if (cone->apex)
		free(cone->apex);
	if (cone->axis)
		free(cone->axis);
	if (cone->color)
		free(cone->color);
	if (cone->texture)
	{
		if (cone->texture->path)
			free(cone->texture->path);
		free(cone->texture);
	}
	free(cone);
}


void	free_light(void *content)
{
	t_light	*light;

	light = (t_light *)content;
	if (!light)
		return ;
	if (light->position)
		free(light->position);
	if (light->color)
		free(light->color);
	free(light);
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
