/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:13:57 by alisharu          #+#    #+#             */
/*   Updated: 2025/11/22 19:13:28 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/validation.h"

static int	is_valid_cone(char **line)
{
	int	len;

	if (!line || ft_strcmp(line[0], "co") != 0)
		return (0);
	len = 0;
	while (line[len])
		len++;
	if (len < 6 || len > 7)
		return (0);
	if (!line[1] || !line[2] || !line[3] || !line[4] || !line[5])
		return (0);
	if (len == 7 && !ft_is_valid_xpm_format(line[6]))
		return (0);
	if (!is_valid_position_vector(line[1])
		|| !is_valid_direction_vector(line[2]) || !is_valid_float(line[3])
		|| !is_valid_float(line[4]) || !is_valid_rgb_argument(line[5]))
		return (0);
	return (1);
}

void	validate_cone(char **map, char **line)
{
	int	len;

	len = matrix_len(line);
	if (len == 7 && line[6] && !ft_is_valid_xpm_path(line[6]))
	{
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_PATH);
	}
	if (!is_valid_cone(line))
	{
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_MAP);
	}
}
