/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:33:43 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/22 21:38:32 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/validation.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_is_valid_xpm_path(char *path)
{
	int		len;
	int		fd;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	validate_map_line(char **map, char **line)
{
	if (!line || !line[0])
		return ;
	if (ft_strcmp(line[0], "A") == 0)
		validate_ambient(map, line);
	else if (ft_strcmp(line[0], "C") == 0)
		validate_camera(map, line);
	else if (ft_strcmp(line[0], "L") == 0)
		validate_light(map, line);
	else if (ft_strcmp(line[0], "sp") == 0)
		validate_sphere(map, line);
	else if (ft_strcmp(line[0], "pl") == 0)
		validate_plane(map, line);
	else if (ft_strcmp(line[0], "cy") == 0)
		validate_cylinder(map, line);
	else if (ft_strcmp(line[0], "co") == 0)
		validate_cone(map, line);
	else
	{
		ft_putstr_fd("Unknown identifier: ", 2);
		ft_putstr_fd(line[0], 2);
		ft_putstr_fd("\n", 2);
		ft_free_matrix(line);
		ft_free_matrix(map);
		error_handling(INVALID_MAP);
	}
}

void	minimum_valid_object(t_valid_object *obj, char **split_line)
{
	if (!split_line || !split_line[0])
		return ;
	if (ft_strcmp(split_line[0], "C") == 0)
		obj->camera = true;
	else if (ft_strcmp(split_line[0], "A") == 0)
		obj->ambient = true;
	else if (ft_strcmp(split_line[0], "L") == 0)
		obj->light = true;
}

void	check_minimum_valid_object(t_valid_object obj, char **map)
{
	if (obj.camera == false || obj.ambient == false || obj.light == false)
	{
		ft_free_matrix(map);
		error_handling(INVALID_MAP);
	}
}

void	validate_map(char **map)
{
	t_valid_object	obj;
	char			**split_line;
	int				i;

	i = -1;
	obj.camera = false;
	obj.light = false;
	obj.ambient = false;
	while (map[++i] != NULL)
	{
		split_line = ft_split(map[i], ' ');
		if (!split_line)
			error_handling(MALLOC_ERROR);
		minimum_valid_object(&obj, split_line);
		validate_map_line(map, split_line);
		ft_free_matrix(split_line);
	}
	check_minimum_valid_object(obj, map);
}
