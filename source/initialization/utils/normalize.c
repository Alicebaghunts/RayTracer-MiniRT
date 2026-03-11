/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:23:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/24 16:54:17 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/initialization.h"

static void	normalize_camera_direction(t_camera *camera)
{
	if (camera && camera->direction)
		*camera->direction = normalize(*camera->direction);
}

static void	normalize_object_direction(t_object *object)
{
	if (object)
	{
		if (object->type == 'p' && object->data->plane
			&& object->data->plane->normal)
			*object->data->plane->normal
				= normalize(*object->data->plane->normal);
		else if (object->type == 'c' && object->data->cylinder
			&& object->data->cylinder->direction)
			*object->data->cylinder->direction
				= normalize(*object->data->cylinder->direction);
	}
}

void	normalize_vectors(t_scene *scene)
{
	t_list		*node;
	t_camera	*camera;
	t_object	*object;

	if (!scene)
		return ;
	node = scene->camera;
	while (node)
	{
		camera = (t_camera *)node->content;
		normalize_camera_direction(camera);
		node = node->next;
	}
	node = scene->objects;
	while (node)
	{
		object = (t_object *)node->content;
		normalize_object_direction(object);
		node = node->next;
	}
}

t_vector	normalize(t_vector vector)
{
	double		length;
	t_vector	result;

	length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z);
	if (length == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	result.x = vector.x / length;
	result.y = vector.y / length;
	result.z = vector.z / length;
	return (result);
}

t_vector	vector_normalize(t_vector v)
{
	double		len;
	t_vector	res;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0.0)
		return ((t_vector){0, 0, 0});
	res.x = v.x / len;
	res.y = v.y / len;
	res.z = v.z / len;
	return (res);
}
