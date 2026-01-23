/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:20:06 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/23 11:17:57 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADE_HELPERS_H
# define SHADE_HELPERS_H

# include "intersect.h"
# include "rendering.h"

/* ----------------------- texture UV ---------------------- */
void		get_uv(t_vector n, double *u, double *v);

/* ----------------------- texture sampling ------------------------- */
t_color		read_texture_pixel(t_texture *tex, int x, int y);
t_color		get_texture_color_uv(t_texture *tex, double u, double v);

t_color		get_sphere_texture_color(t_sphere *sphere, t_texture *tex,
				t_vector hit_point);

/* ----------------------- checkerboards --------------------------------- */
t_color		get_sphere_checkerboard(t_sphere *sphere, t_vector hit_point);
t_color		get_plane_checkerboard(t_plane *pl, t_vector hit_point);
t_color		get_cylinder_checkerboard(t_cylinder *cy, t_vector hit_point);
t_color		get_cone_checkerboard(t_cone *cone, t_vector hit_point);
t_color		get_object_checkerboard(t_object *obj, t_vector hit_point);

/* ----------------------- bump maps --------------------------------- */
double		color_to_height(t_color c);
t_vector	get_sphere_bump_normal(t_sphere *sphere, t_texture *bump,
				t_vector hit_point, t_vector normal);
t_vector	get_object_bump_normal(t_object *obj, t_texture *bump,
				t_vector hit_point, t_vector normal);

/* ----------------------- basis helpers --------------------------------- */
t_vector	get_axis_up(t_vector axis);
void		get_basis_from_axis(t_vector axis, t_vector *t, t_vector *b);

#endif
