/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_checkerboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:12:00 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 21:17:29 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

static t_color	checker_from_uv(int u, int v)
{
	if ((u + v) % 2 == 0)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

static int	is_base_hit(t_cone *co, t_vector rel, t_vector axis)
{
	double	h;

	h = co->height;
	if (h <= 0.0)
		h = 1.0;
	if (fabs(vector_dot(rel, axis) - h) <= 1e-6)
		return (1);
	return (0);
}

static t_color	get_cone_side_checker(t_cone *co, t_vector rel, t_vector axis,
		t_vector tb[2])
{
	double	ang;
	double	h;
	double	v;
	int		uvi[2];

	ang = wrap_angle(atan2(vector_dot(rel, tb[1]), vector_dot(rel, tb[0])));
	if (co->height > 0.0)
		h = co->height;
	else
		h = 1.0;
	v = vector_dot(rel, axis) / h;
	uvi[0] = (int)floor((ang / (2.0 * M_PI)) * 10.0);
	uvi[1] = (int)floor(v * 10.0);
	return (checker_from_uv(uvi[0], uvi[1]));
}

static t_color	get_cone_base_checker(t_cone *co, t_vector rel, t_vector axis,
		t_vector tb[2])
{
	t_vector	base_rel;
	double		r;
	double		step;
	double		h;
	int			uvi[2];

	h = 0.0;
	if (co->height > 0.0)
		h = co->height;
	else
		h = 1.0;
	base_rel = vector_sub(rel, vector_scale(axis, h));
	if (co->angle != 0.0)
		r = fabs(tan(co->angle) * h);
	else
		r = 1.0;
	if (r <= 0.0)
		r = 1.0;
	step = (2.0 * M_PI * r) / 10.0;
	uvi[0] = (int)floor(vector_dot(base_rel, tb[0]) / step);
	uvi[1] = (int)floor(vector_dot(base_rel, tb[1]) / step);
	return (checker_from_uv(uvi[0], uvi[1]));
}

t_color	get_cone_checkerboard(t_cone *cone, t_vector hit_point)
{
	t_vector	axis;
	t_vector	rel;
	t_vector	tb[2];

	axis = normalize(*(cone->axis));
	rel = vector_sub(hit_point, *(cone->apex));
	get_cone_basis(axis, &tb[0], &tb[1]);
	if (is_base_hit(cone, rel, axis))
		return (get_cone_base_checker(cone, rel, axis, tb));
	return (get_cone_side_checker(cone, rel, axis, tb));
}
