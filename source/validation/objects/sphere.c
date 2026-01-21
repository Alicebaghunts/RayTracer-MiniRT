/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:33:49 by alisharu          #+#    #+#             */
/*   Updated: 2025/11/22 19:13:07 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

static int	is_valid_sphere(char **line)
{
	int	len;

	if (!line || ft_strcmp(line[0], "sp") != 0)
		return (0);
	len = 0;
	while (line[len])
		len++;
	if (len < 4 || len > 6)
		return (0);
	if (len >= 5 && !ft_is_valid_xpm_format(line[4]))
		return (0);
	if (len == 6 && !ft_is_valid_xpm_format(line[5]))
		return (0);
	if (!is_valid_position_vector(line[1]))
		return (0);
	if (!is_valid_diameter(line[2]))
		return (0);
	if (!is_valid_rgb_argument(line[3]))
		return (0);
	return (1);
}

void	validate_sphere(char **map, char **line)
{
	int	len;

	len = matrix_len(line);
	if ((len >= 5 && line[4] && !ft_is_valid_xpm_path(line[4]))
		|| (len >= 6 && line[5] && !ft_is_valid_xpm_path(line[5])))
	{
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_PATH);
	}
	if (!is_valid_sphere(line))
	{
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_MAP);
	}
}
