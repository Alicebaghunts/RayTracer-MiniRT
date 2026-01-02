/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:53:28 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/25 19:40:25 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

int	cmp_types_and_init(char **line, t_object *object)
{
	if (ft_strncmp(line[0], "sp", 2) == 0)
	{
		object->type = 's';
		object->data->sphere = init_sphere(line);
		return (object->data->sphere == NULL);
	}
	else if (ft_strncmp(line[0], "pl", 2) == 0)
	{
		object->type = 'p';
		object->data->plane = init_plane(line);
		return (object->data->plane == NULL);
	}
	else if (ft_strncmp(line[0], "cy", 2) == 0)
	{
		object->type = 'c';
		object->data->cylinder = init_cylinder(line);
		return (object->data->cylinder == NULL);
	}
	else if (ft_strncmp(line[0], "co", 2) == 0)
	{
		object->type = 'o';
		object->data->cone = init_cone(line);
		return (object->data->cone == NULL);
	}
	return (0);
}

static t_object	*create_object(t_scene *scene, char **line, char **map)
{
	t_object	*object;

	object = ft_calloc(1, sizeof(t_object));
	if (!object)
	{
		free_scene_inits(scene, line, map);
		error_handling(MALLOC_ERROR);
	}
	object->data = ft_calloc(1, sizeof(t_object_data));
	if (!object->data)
	{
		free(object);
		free_scene_inits(scene, line, map);
		error_handling(MALLOC_ERROR);
	}
	if (cmp_types_and_init(line, object) == 1)
	{
		free(object->data);
		free(object);
		free_scene_inits(scene, line, map);
		error_handling(MALLOC_ERROR);
	}
	return (object);
}

void	init_objects(t_scene *scene, char **line, char **map)
{
	t_object	*object;
	t_list		*node;

	object = create_object(scene, line, map);
	node = ft_lstnew(object);
	if (!node)
	{
		free(object->data);
		free(object);
		free_scene_inits(scene, line, map);
		error_handling(MALLOC_ERROR);
	}
	ft_lstadd_back(&scene->objects, node);
}
