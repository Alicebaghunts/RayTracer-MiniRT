/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:32:12 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/24 16:29:51 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/initialization.h"

static int	fill_sphere_vectors(t_sphere *sphere, char **pos, char **col)
{
	if (!pos || !col)
		return (0);
	sphere->position = ft_calloc(1, sizeof(t_vector));
	if (!sphere->position)
		return (0);
	sphere->color = ft_calloc(1, sizeof(t_color));
	if (!sphere->color)
		return (free(sphere->position), 0);
	sphere->position->x = ft_atof(pos[0]);
	sphere->position->y = ft_atof(pos[1]);
	sphere->position->z = ft_atof(pos[2]);
	sphere->color->red = ft_atoi(col[0]);
	sphere->color->green = ft_atoi(col[1]);
	sphere->color->blue = ft_atoi(col[2]);
	return (1);
}

static int	validate_sphere_splits(char **pos, char **col)
{
	if (!pos || !col || matrix_len(pos) != 3 || matrix_len(col) != 3)
		return (0);
	if (!pos[0] || !pos[1] || !pos[2] || !col[0] || !col[1] || !col[2])
		return (0);
	return (1);
}

static void	load_sphere_textures(t_sphere *sphere, char **line, int line_count)
{
	if (line_count > 4 && line[4] && ft_strlen(line[4]) > 0)
		sphere->texture = init_texture(line[4]);
	if (line_count > 5 && line[5] && ft_strlen(line[5]) > 0)
		sphere->bump = init_texture(line[5]);
}

t_sphere	*init_sphere(char **line)
{
	t_sphere	*sphere;
	char		**pos;
	char		**col;
	int			line_count;

	if (!line || !line[1] || !line[2] || !line[3])
		return (NULL);
	line_count = matrix_len(line);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	pos = ft_split(line[1], ',');
	col = ft_split(line[3], ',');
	if (!validate_sphere_splits(pos, col))
		return (ft_free_matrix(pos), ft_free_matrix(col), free(sphere), NULL);
	if (!fill_sphere_vectors(sphere, pos, col))
		return (ft_free_matrix(pos), ft_free_matrix(col), free(sphere), NULL);
	sphere->diameter = ft_atof(line[2]);
	ft_free_matrix(pos);
	ft_free_matrix(col);
	load_sphere_textures(sphere, line, line_count);
	return (sphere);
}
