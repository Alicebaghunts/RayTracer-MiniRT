/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:31:59 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/24 16:34:54 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

static int	fill_cylinder_vectors(t_cylinder *cylinder, char **pos, char **dir,
		char **col)
{
	if (!pos || !dir || !col)
		return (0);
	cylinder->position = ft_calloc(1, sizeof(t_vector));
	if (!cylinder->position)
		return (0);
	cylinder->direction = ft_calloc(1, sizeof(t_vector));
	if (!cylinder->direction)
		return (free(cylinder->position), 0);
	cylinder->color = ft_calloc(1, sizeof(t_color));
	if (!cylinder->color)
		return (free(cylinder->position), free(cylinder->direction), 0);
	cylinder->position->x = ft_atof(pos[0]);
	cylinder->position->y = ft_atof(pos[1]);
	cylinder->position->z = ft_atof(pos[2]);
	cylinder->direction->x = ft_atof(dir[0]);
	cylinder->direction->y = ft_atof(dir[1]);
	cylinder->direction->z = ft_atof(dir[2]);
	cylinder->color->red = ft_atoi(col[0]);
	cylinder->color->green = ft_atoi(col[1]);
	cylinder->color->blue = ft_atoi(col[2]);
	return (1);
}

static int	load_cylinder_textures(t_cylinder *cylinder, char **line,
		int line_count)
{
	if (line_count > 6 && line[6])
	{
		cylinder->texture = init_texture(line[6]);
		if (!cylinder->texture)
			return (0);
	}
	if (line_count > 7 && line[7])
	{
		cylinder->bump = init_texture(line[7]);
		if (!cylinder->bump)
			return (0);
	}
	return (1);
}

static t_cylinder	*finalize_cylinder(t_cylinder *cylinder, char **line,
		int line_count)
{
	if (!load_cylinder_textures(cylinder, line, line_count))
		return (free_cylinder(cylinder), NULL);
	return (cylinder);
}

t_cylinder	*init_cylinder(char **line)
{
	t_cylinder	*cylinder;
	char		**pos;
	char		**dir;
	char		**col;
	int			line_count;

	if (!line || !line[1] || !line[2] || !line[3] || !line[4] || !line[5])
		return (NULL);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	pos = ft_split(line[1], ',');
	dir = ft_split(line[2], ',');
	col = ft_split(line[5], ',');
	if (!fill_cylinder_vectors(cylinder, pos, dir, col))
		return (ft_free_matrix(pos), ft_free_matrix(dir),
			ft_free_matrix(col), free(cylinder), NULL);
	cylinder->diameter = ft_atof(line[3]);
	cylinder->height = ft_atof(line[4]);
	ft_free_matrix(pos);
	ft_free_matrix(dir);
	ft_free_matrix(col);
	line_count = matrix_len(line);
	return (finalize_cylinder(cylinder, line, line_count));
}
