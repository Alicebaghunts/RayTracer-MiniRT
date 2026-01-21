/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:32:03 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/21 09:11:19 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

static t_light	*create_light(char **line)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = init_vector(line[1]);
	light->brightness_ratio = ft_atof(line[2]);
	light->color = parse_color(line[3]);
	if (!light->position || !light->color)
	{
		if (light->position)
			free(light->position);
		if (light->color)
			free(light->color);
		free(light);
		return (NULL);
	}
	return (light);
}

static void	add_light_to_scene(t_scene *scene, t_light *light)
{
	t_list	*node;

	node = ft_lstnew(light);
	if (!node)
	{
		free(light);
		free_scene_inits(scene, NULL, NULL);
		error_handling(MALLOC_ERROR);
	}
	ft_lstadd_back(&scene->lights, node);
}

void	init_light(t_scene *scene, char **line, char **map)
{
	t_light	*light;

	light = create_light(line);
	if (!light)
	{
		free_scene_inits(scene, line, map);
		error_handling(MALLOC_ERROR);
	}
	add_light_to_scene(scene, light);
}
