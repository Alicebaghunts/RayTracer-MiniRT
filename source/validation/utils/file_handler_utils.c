/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:05:05 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/22 21:38:25 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int	ft_is_valid_xpm_format(char *path)
{
	int		len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	return (1);
}

int	checking_argument(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	check_extension(char *path)
{
	char	*dot;

	dot = ft_strrchr(path, '.');
	if (!dot || ft_strcmp(dot, ".rt"))
		return (0);
	return (1);
}

void	ft_free_matrix(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	matrix_len(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
}
