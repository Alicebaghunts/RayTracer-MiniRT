/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 18:19:42 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/02 17:31:39 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_types.h"
#include "initialization.h"
#include "mlx.h"
#include <stdlib.h>
#include <string.h>

t_texture	*init_texture(char *path)
{
	t_texture	*texture;

	if (!path || strlen(path) == 0)
		return (NULL);
	texture = ft_calloc(1, sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->path = ft_strdup(path);
	if (!texture->path)
	{
		free(texture);
		return (NULL);
	}
	texture->img = NULL;
	texture->addr = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->size_line = 0;
	texture->endian = 0;
	return (texture);
}

static void	load_texture_image(void *mlx, t_texture *texture)
{
	if (!texture || !texture->path || texture->img)
		return ;
	texture->img = mlx_xpm_file_to_image(mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img)
		return ;
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
}

void	load_scene_textures(t_scene *scene, void *mlx)
{
	t_list		*node;
	t_object	*obj;

	if (!scene || !mlx)
		return ;
	node = scene->objects;
	while (node)
	{
		obj = (t_object *)node->content;
		if (obj && obj->type == 's' && obj->data
			&& obj->data->sphere)
		{
			if (obj->data->sphere->texture)
				load_texture_image(mlx, obj->data->sphere->texture);
			if (obj->data->sphere->bump)
				load_texture_image(mlx, obj->data->sphere->bump);
		}
		node = node->next;
	}
}
