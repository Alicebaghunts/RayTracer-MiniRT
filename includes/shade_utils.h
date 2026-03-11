/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:20:29 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/23 11:36:19 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADE_UTILS_H
# define SHADE_UTILS_H

# include "intersect.h"
# include "rendering.h"

/* --------------- texture helpers -----------------------------*/
t_color		get_sphere_texture_color(t_sphere *sphere, t_texture *tex,
				t_vector hit_point);
t_color		get_texture_color_uv(t_texture *tex, double u, double v);
double		color_to_height(t_color c);

/* --------------- erboard helpers ------------------------------ */
t_color		get_sphere_erboard(t_sphere *sphere, t_vector hit_point);
t_color		get_plane_erboard(t_plane *pl, t_vector hit_point);
t_color		get_cylinder_erboard(t_cylinder *cy, t_vector hit_point);
t_color		get_cone_erboard(t_cone *cone, t_vector hit_point);
t_color		get_object_erboard(t_object *obj, t_vector hit_point);

/* ---------------- bump helpers --------------------------------- */

t_vector	get_sphere_bump_normal(t_sphere *sphere, t_texture *bump,
				t_vector hit_point, t_vector normal);
t_vector	get_object_bump_normal(t_object *obj, t_texture *bump,
				t_vector hit_point, t_vector normal);

/* ---------------- lights helpers ------------------------- */

void		init_light_info_base(t_light_info *li, t_shade_info *si,
				t_light *light);
void		compute_lights(t_shade_info info);

/* ---------------- shade helpers --------------------------*/
t_color		determine_obj_color(t_scene *scene, t_object *obj,
				t_vector hit_point);
t_vector	compute_final_normal(t_scene *scene, t_object *obj,
				t_vector hit_point, t_vector normal);

#endif
