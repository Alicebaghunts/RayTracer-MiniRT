/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:34:10 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/18 19:59:51 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/validation.h"

static char	**malloc_copy_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 10);
	if (!map)
		error_handling(MALLOC_ERROR);
	return (map);
}

static char	**resize_map(char **map, int *map_size)
{
	char	**new_map;
	int		i;

	*map_size *= 2;
	new_map = (char **)malloc(sizeof(char *) * (*map_size));
	if (!new_map)
		error_handling(MALLOC_ERROR);
	i = 0;
	while (i < *map_size / 2)
	{
		new_map[i] = map[i];
		i++;
	}
	free(map);
	return (new_map);
}

static void	check_height(int height, char **map)
{
	if (height == 0)
	{
		free(map);
		error_handling(INVALID_MAP);
	}
}

char	**read_in_map_file(int fd)
{
	char	**map;
	char	*line;
	char	*readline;
	int		height;
	int		map_size;

	map = malloc_copy_map();
	map_size = 10;
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		readline = ft_strtrim(line, "\n");
		free(line);
		if (!readline)
			error_handling(MALLOC_ERROR);
		if (height >= map_size)
			map = resize_map(map, &map_size);
		map[height++] = readline;
		line = get_next_line(fd);
	}
	check_height(height, map);
	return (map[height] = NULL, map);
}

int	check_and_open_map_file(char *path)
{
	char	**split;
	int		fd;

	if (checking_argument(path) == 0)
		error_handling(INVALID_PATH);
	split = ft_split(path, ' ');
	if (split == NULL)
		error_handling(INVALID_PATH);
	if (split[1] != NULL)
	{
		ft_free_matrix(split);
		error_handling(INVALID_PATH);
	}
	if (!check_extension(path))
	{
		ft_free_matrix(split);
		error_handling(INVALID_PATH);
	}
	fd = open(split[0], O_RDONLY);
	ft_free_matrix(split);
	if (fd == -1)
		error_handling(INVALID_FILE);
	return (fd);
}
