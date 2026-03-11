/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:10:50 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 13:55:16 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"
#include "../../../includes/shade_helpers.h"

static t_vector	get_sphere_n(t_sphere *sp, t_vector hit)
{
	return (normalize(vector_sub(hit, *(sp->position))));
}

static void	get_sphere_uv(t_vector n, double *uv)
{
	uv[0] = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	uv[1] = 0.5 - asin(n.y) / M_PI;
}

static t_vector	get_sphere_tangent(t_vector n)
{
	t_vector	up;

	if (fabs(n.y) > 0.999)
		up = (t_vector){1, 0, 0};
	else
		up = (t_vector){0, 1, 0};
	return (normalize(vector_cross(n, up)));
}

static t_vector	get_bump_offset(t_texture *bump, double *uv, t_vector n)
{
	double		du;
	double		dv;
	double		h[3];
	t_vector	t;
	t_vector	b;

	du = 1.0 / bump->width;
	dv = 1.0 / bump->height;
	h[0] = color_to_height(get_texture_color_uv(bump, uv[0], uv[1]));
	h[1] = color_to_height(get_texture_color_uv(bump, uv[0] + du, uv[1]));
	h[2] = color_to_height(get_texture_color_uv(bump, uv[0], uv[1] + dv));
	t = get_sphere_tangent(n);
	b = normalize(vector_cross(t, n));
	return (vector_addition(
			vector_scale(t, (h[1] - h[0]) * 3.0),
			vector_scale(b, (h[2] - h[0]) * 3.0)));
}

t_vector	get_sphere_bump_normal(t_sphere *sphere, t_texture *bump,
			t_vector hit_point, t_vector normal)
{
	t_vector	n;
	double		uv[2];
	t_vector	offset;

	if (!sphere || !bump || !bump->addr || bump->width <= 0
		|| bump->height <= 0)
		return (normal);
	n = get_sphere_n(sphere, hit_point);
	get_sphere_uv(n, uv);
	offset = get_bump_offset(bump, uv, n);
	return (normalize(vector_addition(n, offset)));
}
