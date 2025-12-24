/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:21:37 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/24 16:34:54 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

static int	fill_cone_vectors(t_cone *cone, char **pos, char **axis, char **col)
{
	if (!pos || !axis || !col)
		return (0);
	cone->apex = ft_calloc(1, sizeof(t_vector));
	if (!cone->apex)
		return (0);
	cone->axis = ft_calloc(1, sizeof(t_vector));
	if (!cone->axis)
		return (free(cone->apex), 0);
	cone->color = ft_calloc(1, sizeof(t_color));
	if (!cone->color)
		return (free(cone->apex), free(cone->axis), 0);
	cone->apex->x = ft_atof(pos[0]);
	cone->apex->y = ft_atof(pos[1]);
	cone->apex->z = ft_atof(pos[2]);
	cone->axis->x = ft_atof(axis[0]);
	cone->axis->y = ft_atof(axis[1]);
	cone->axis->z = ft_atof(axis[2]);
	*cone->axis = normalize(*cone->axis);
	cone->color->red = ft_atoi(col[0]);
	cone->color->green = ft_atoi(col[1]);
	cone->color->blue = ft_atoi(col[2]);
	return (1);
}

static int	load_cone_textures(t_cone *cone, char **line, int line_count)
{
	if (line_count > 6 && line[6])
	{
		cone->texture = init_texture(line[6]);
		if (!cone->texture)
			return (0);
	}
	if (line_count > 7 && line[7])
	{
		cone->bump = init_texture(line[7]);
		if (!cone->bump)
			return (0);
	}
	return (1);
}

static void	setup_cone_geometry(t_cone *cone, char **line)
{
	cone->angle = (ft_atof(line[3]) * 3.0) * M_PI / 180.0;
	cone->height = ft_atof(line[4]);
	if (cone->height < 0)
	{
		*(cone->axis) = vector_scale(*(cone->axis), -1);
		cone->height = -cone->height;
	}
	*(cone->axis) = normalize(vector_scale(*(cone->axis), -1));
}

t_cone	*init_cone(char **line)
{
	t_cone	*cone;
	char	**pos;
	char	**axis;
	char	**col;
	int		line_count;

	if (!line || !line[1] || !line[2] || !line[3] || !line[4] || !line[5])
		return (NULL);
	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (NULL);
	pos = ft_split(line[1], ',');
	axis = ft_split(line[2], ',');
	col = ft_split(line[5], ',');
	if (!fill_cone_vectors(cone, pos, axis, col))
		return (ft_free_matrix(pos), ft_free_matrix(axis),
			ft_free_matrix(col), free(cone), NULL);
	setup_cone_geometry(cone, line);
	ft_free_matrix(pos);
	ft_free_matrix(axis);
	ft_free_matrix(col);
	line_count = matrix_len(line);
	if (!load_cone_textures(cone, line, line_count))
		return (free_cone(cone), NULL);
	return (cone);
}
