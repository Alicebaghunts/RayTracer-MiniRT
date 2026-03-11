/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:34:24 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/24 20:22:29 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/validation.h"

static int	is_valid_ambient(char **line)
{
	if (!line || ft_strcmp(line[0], "A") != 0)
		return (0);
	if (!line[1] || !line[2] || line[3])
		return (0);
	if (!is_valid_brightness_ratio(line[1]))
		return (0);
	if (!is_valid_rgb_argument(line[2]))
		return (0);
	return (1);
}

void	validate_ambient(char **map, char **line)
{
	if (!is_valid_ambient(line))
	{
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_MAP);
	}
}
