/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:44:24 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/24 16:38:47 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/intersect.h"

t_quad	cylinder_coeffs(t_vector dir, t_vector oc, t_vector axis, double radius)
{
	t_vector	d_proj;
	t_vector	oc_proj;
	t_quad		q;

	d_proj = vector_sub(dir, vector_scale(axis, vector_dot(dir, axis)));
	oc_proj = vector_sub(oc, vector_scale(axis, vector_dot(oc, axis)));
	q.a = vector_dot(d_proj, d_proj);
	q.b = 2.0 * vector_dot(oc_proj, d_proj);
	q.c = vector_dot(oc_proj, oc_proj) - radius * radius;
	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}

double	pick_root(t_quad q)
{
	double	t1;
	double	t2;

	if (q.discriminant < 0)
		return (-1.0);
	t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	if (t1 > 1e-6)
		return (t1);
	if (t2 > 1e-6)
		return (t2);
	return (-1.0);
}

t_vector	compute_hit(t_camera *cam, t_vector dir, double t)
{
	return (vector_addition(*(cam->position), vector_scale(dir, t)));
}

double	intersect_cylinder(t_ray_data data, t_hit_type *hit_type)
{
	double	t_side;
	double	t_caps;

	t_side = intersect_cylinder_side(data, hit_type);
	t_caps = intersect_cylinder_caps(data, hit_type);
	if (t_side < 0 && t_caps < 0)
		return (-1.0);
	if (t_side < 0)
		return (t_caps);
	if (t_caps < 0)
	{
		*hit_type = HIT_CYLINDER_SIDE;
		return (t_side);
	}
	if (t_side < t_caps)
	{
		*hit_type = HIT_CYLINDER_SIDE;
		return (t_side);
	}
	return (t_caps);
}
