/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:34:15 by alisharu          #+#    #+#             */
/*   Updated: 2025/11/22 18:50:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "validation.h"

static int	is_valid_cylinder(char **line)
{
	int	len;

	if (!line || ft_strcmp(line[0], "cy") != 0)
		return (0);
	len = 0;
	while (line[len])
		len++;
	if (len < 6 || len > 7)
		return (0);
	if (len == 7 && !ft_is_valid_xpm_path(line[6]))
		return (0);
	if (!is_valid_position_vector(line[1]))
		return (0);
	if (!is_valid_direction_vector(line[2]))
		return (0);
	if (!is_valid_diameter(line[3]))
		return (0);
	if (!is_valid_diameter(line[4]))
		return (0);
	if (!is_valid_rgb_argument(line[5]))
		return (0);
	return (1);
}

void	validate_cylinder(char **map, char **line)
{
	int	len;

	len = matrix_len(line);
	if (len == 7 && line[6] && !ft_is_valid_xpm_path(line[6]))
	{
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_PATH);
	}
	if (!is_valid_cylinder(line))
	{
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_MAP);
	}
}
