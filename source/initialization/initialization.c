/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:29:37 by alisharu          #+#    #+#             */
/*   Updated: 2025/10/08 14:29:26 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

void	fill_scene_with_line(t_scene *scene, char **line, char **map)
{
	if (!scene || !line || !line[0])
		return ;
	if (ft_strcmp(line[0], "A") == 0)
		init_ambient(scene, line, map);
	else if (ft_strcmp(line[0], "C") == 0)
		init_camera(scene, line, map);
	else if (ft_strcmp(line[0], "L") == 0)
		init_light(scene, line, map);
	else if (ft_strcmp(line[0], "sp") == 0 || ft_strcmp(line[0], "pl") == 0
		|| ft_strcmp(line[0], "cy") == 0 || ft_strcmp(line[0], "co") == 0)
		init_objects(scene, line, map);
}

t_scene	*initialize_scene(char **map)
{
	t_scene	*scene;
	char	**split_line;
	int		i;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		error_handling(MALLOC_ERROR);
	scene->selected_object = NULL;
	scene->selected_mode = MODE_TEXTURE;
	i = -1;
	while (map[++i])
	{
		split_line = ft_split(map[i], ' ');
		if (!split_line)
		{
			free_scene_inits(scene, split_line, map);
			error_handling(MALLOC_ERROR);
		}
		fill_scene_with_line(scene, split_line, map);
		ft_free_matrix(split_line);
	}
	return (scene);
}
