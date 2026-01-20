/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:08:23 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 15:02:08 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include <math.h>

static t_vector	get_up_axis(t_vector axis)
{
	if (fabs(axis.y) > 0.999)
		return ((t_vector){1.0, 0.0, 0.0});
	return ((t_vector){0.0, 1.0, 0.0});
}

static void	get_cy_basis(t_vector axis, t_vector *t, t_vector *b)
{
	t_vector	up;

	up = get_up_axis(axis);
	*t = normalize(vector_cross(up, axis));
	*b = normalize(vector_cross(axis, *t));
}

static double	wrap_angle(double ang)
{
	if (ang < 0.0)
		ang += 2.0 * M_PI;
	return (ang);
}

static t_color	checker_from_uv(int u, int v)
{
	if ((u + v) % 2 == 0)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

static int	is_cap_hit(t_cylinder *cy, t_vector rel, t_vector axis)
{
	double	hp;

	hp = cy->height * 0.5;
	if (fabs(vector_dot(rel, axis)) >= hp - 1e-6)
		return (1);
	return (0);
}

static t_color	get_cy_side_checker(t_cylinder *cy, t_vector rel, t_vector axis,
		t_vector tb[2])
{
	double	ang;
	double	h;
	double	v;
	int		uvi[2];

	ang = wrap_angle(atan2(vector_dot(rel, tb[1]), vector_dot(rel, tb[0])));
	h = (cy->height > 0.0) ? cy->height : 1.0;
	v = (vector_dot(rel, axis) + h * 0.5) / h;
	uvi[0] = (int)floor((ang / (2.0 * M_PI)) * 10.0);
	uvi[1] = (int)floor(v * 10.0);
	return (checker_from_uv(uvi[0], uvi[1]));
}

static t_color	get_cy_cap_checker(t_cylinder *cy, t_vector rel, t_vector axis,
		t_vector tb[2])
{
	t_vector	cap_rel;
	double	hp;
	double	r;
	double	step;
	int		uvi[2];

	hp = cy->height * 0.5;
	if (vector_dot(rel, axis) > 0.0)
		cap_rel = vector_sub(rel, vector_scale(axis, hp));
	else
		cap_rel = vector_addition(rel, vector_scale(axis, hp));
	if (cy->diameter > 0.0)
		r = cy->diameter / 2.0;
	else
		r = 1.0;
	step = (2.0 * M_PI * r) / 10.0;
	uvi[0] = (int)floor(vector_dot(cap_rel, tb[0]) / step);
	uvi[1] = (int)floor(vector_dot(cap_rel, tb[1]) / step);
	if ((uvi[0] + uvi[1]) % 2 == 0)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

t_color	get_cylinder_checkerboard(t_cylinder *cy, t_vector hit_point)
{
	t_vector	axis;
	t_vector	rel;
	t_vector	tb[2];

	axis = normalize(*(cy->direction));
	rel = vector_sub(hit_point, *(cy->position));
	get_cy_basis(axis, &tb[0], &tb[1]);
	if (is_cap_hit(cy, rel, axis))
		return (get_cy_cap_checker(cy, rel, axis, tb));
	return (get_cy_side_checker(cy, rel, axis, tb));
}
