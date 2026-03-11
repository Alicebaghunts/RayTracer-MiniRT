/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:33:54 by alisharu          #+#    #+#             */
/*   Updated: 2025/11/22 18:49:21 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/validation.h"

static int	is_valid_plane(char **line)
{
	int	len;

	if (!line || ft_strcmp(line[0], "pl") != 0)
		return (0);
	len = 0;
	while (line[len])
		len++;
	if (len < 4 || len > 5)
		return (0);
	if (len == 5 && !ft_is_valid_xpm_path(line[4]))
		return (0);
	if (!is_valid_position_vector(line[1]))
		return (0);
	if (!is_valid_position_vector(line[2]))
		return (0);
	if (!is_valid_rgb_argument(line[3]))
		return (0);
	return (1);
}

void	validate_plane(char **map, char **line)
{
	if (!is_valid_plane(line))
	{
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_MAP);
	}
}
