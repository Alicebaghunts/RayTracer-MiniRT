/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:22:37 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 21:31:22 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "rendering.h"

t_quad	cone_quadratic(t_vector dir, t_vector oc, t_vector v,
		double cos_angle)
{
	t_quad	q;

	q.a = pow(vector_dot(dir, v), 2.0) - cos_angle * cos_angle
		* vector_dot(dir, dir);
	q.b = 2.0 * (vector_dot(dir, v) * vector_dot(oc, v)
			- cos_angle * cos_angle * vector_dot(dir, oc));
	q.c = pow(vector_dot(oc, v), 2.0) - cos_angle * cos_angle
		* vector_dot(oc, oc);
	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}

t_disk	cone_base_disk(t_cone *cone, t_vector v)
{
	t_disk	d;

	d.center = vector_addition(*(cone->apex), vector_scale(v, cone->height));
	d.normal = v;
	d.radius = fabs(tan(cone->angle) * cone->height);
	return (d);
}

double	cone_side_shadow(t_vector origin, t_vector dir, t_cone *cone)
{
	t_vector	oc;
	t_vector	v;
	t_quad		q;
	double		ca;

	v = normalize(*(cone->axis));
	oc = vector_sub(origin, *(cone->apex));
	ca = cos(cone->angle);
	q = cone_quadratic(dir, oc, v, ca);
	if (q.discriminant < 0.0)
		return (-1.0);
	return (select_cone_root(q, dir, oc, cone));
}

double	intersect_cone_shadow(t_vector origin, t_vector dir, t_cone *cone)
{
	t_vector	v;
	t_disk		disk;
	double		t[2];

	v = normalize(*(cone->axis));
	t[0] = cone_side_shadow(origin, dir, cone);
	disk = cone_base_disk(cone, v);
	t[1] = check_disk_hit_shadow(origin, dir, disk);
	if (t[1] > 0.0 && (t[0] < 0.0 || t[1] < t[0]))
		return (t[1]);
	return (t[0]);
}
