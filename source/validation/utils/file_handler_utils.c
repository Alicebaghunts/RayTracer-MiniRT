/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:05:05 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/16 17:11:41 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

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
