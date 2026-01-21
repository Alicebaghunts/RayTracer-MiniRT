/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:31:40 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/21 10:05:54 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

t_color	*parse_color(char *line)
{
	t_color	*color;
	char	**matrix_color;

	if (!line)
		return (NULL);
	matrix_color = ft_split(line, ',');
	if (!matrix_color)
		return (NULL);
	color = malloc(sizeof(t_color));
	if (!color)
	{
		ft_free_matrix(matrix_color);
		return (NULL);
	}
	color->red = ft_atoi(matrix_color[0]);
	color->green = ft_atoi(matrix_color[1]);
	color->blue = ft_atoi(matrix_color[2]);
	ft_free_matrix(matrix_color);
	matrix_color = NULL;
	return (color);
}

void	init_ambient(t_scene *scene, char **line, char **map)
{
	scene->ambient = ft_calloc(1, sizeof(t_ambient));
	if (!scene->ambient)
	{
		free_scene_inits(scene, line, map);
		error_handling(MALLOC_ERROR);
	}
	scene->ambient->light_ratio = ft_atof(line[1]);
	scene->ambient->color = parse_color(line[2]);
	if (scene->ambient->color == NULL)
	{
		free(scene->ambient);
		scene->ambient = NULL;
		free_scene_inits(scene, line, map);
		error_handling(MALLOC_ERROR);
	}
}
