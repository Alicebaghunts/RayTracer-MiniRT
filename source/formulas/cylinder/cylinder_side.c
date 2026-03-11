/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_side.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:15:00 by alisharu          #+#    #+#             */
/*   Updated: 2025/10/01 21:59:23 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/intersect.h"

t_quad	cylinder_quadratic(t_vector ray, t_vector oc, t_vector dir,
		double radius)
{
	t_quad	q;

	q.a = vector_dot(ray, ray) - pow(vector_dot(ray, dir), 2);
	q.b = 2 * (vector_dot(ray, oc) - vector_dot(ray, dir) * vector_dot(oc,
				dir));
	q.c = vector_dot(oc, oc) - pow(vector_dot(oc, dir), 2) - radius * radius;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	return (q);
}

double	intersect_cylinder_side(t_ray_data data, t_hit_type *hit_type)
{
	t_vector	oc;
	t_vector	axis;
	t_quad		q;
	double		t_side;
	t_vector	hit;

	*hit_type = HIT_NONE;
	oc = vector_sub(*(data.cam->position), *(data.cy->position));
	axis = normalize(*(data.cy->direction));
	q = cylinder_coeffs(data.ray, oc, axis, data.cy->diameter / 2.0);
	t_side = pick_root(q);
	if (t_side > 0)
	{
		hit = compute_hit(data.cam, data.ray, t_side);
		if (!check_cylinder_height(hit, data.cy, axis))
			t_side = -1.0;
	}
	return (t_side);
}
