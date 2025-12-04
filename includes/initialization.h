/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:30:19 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/01 17:54:06 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZATION_H
# define INITIALIZATION_H

# include "libft.h"
# include "object_types.h"
# include "validation.h"
# include <stdlib.h>

// objects

t_scene		*initialize_scene(char **map);
void		init_ambient(t_scene *scene, char **line, char **map);
void		init_camera(t_scene *scene, char **line, char **map);
void		init_light(t_scene *scene, char **line, char **map);

t_cylinder	*init_cylinder(char **line);
t_plane		*init_plane(char **line);
t_sphere	*init_sphere(char **line);
// void	initialize_scene(t_scene *scene, char **map);

//
t_color		*parse_color(char *line);
t_vector	*init_vector(char *line);

// utils
void		normalize_vectors(t_scene *scene);
t_vector	normalize(t_vector vector);
t_vector	sphere_normal(t_sphere *sphere, t_vector hit_point);
t_vector	cylinder_normal(t_cylinder *cyl, t_vector hit_point);
void		free_scene(t_scene *scene);
void		free_light(void *content);
void		free_object(void *content);
void		free_cone(t_cone *cone);
void		free_camera(void *content);
void		free_cylinder(t_cylinder *cylinder);
void		free_plane(t_plane *plane);
void		free_scene_inits(t_scene *scene, char **line, char **map);
void		init_objects(t_scene *scene, char **line, char **map);
t_texture	*init_texture(char *path);
void		load_scene_textures(t_scene *scene, void *mlx);
int			cmp_types_and_init(char **line, t_object *object);
t_cone		*init_cone(char **line);
#endif
