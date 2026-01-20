/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:44:36 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 15:14:44 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "rendering.h"

static t_quad	cone_shadow_quadratic(t_vector dir, t_vector oc, t_vector v,
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

static double	select_cone_root_shadow(t_quad q, t_vector dir, t_vector oc,
		t_cone *cone)
{
	double		t1;
	double		t2;
	double		best_t;
	t_vector	v;

	v = normalize(*(cone->axis));
	t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	best_t = -1.0;
	if (t1 > 1e-6 && vector_dot(vector_addition(oc, vector_scale(dir, t1)), v)
		>= 0.0 && vector_dot(vector_addition(oc, vector_scale(dir, t1)), v)
		<= cone->height)
		best_t = t1;
	if (t2 > 1e-6 && vector_dot(vector_addition(oc, vector_scale(dir, t2)), v)
		>= 0.0 && vector_dot(vector_addition(oc, vector_scale(dir, t2)), v)
		<= cone->height && (best_t < 0 || t2 < best_t))
		best_t = t2;
	return (best_t);
}

double	intersect_cone_shadow(t_vector origin, t_vector dir, t_cone *cone)
{
	t_vector	oc;
	t_vector	v;
	t_quad		q;
	double		cos_angle;
	double		t_side;
	double		t_cap;
	t_disk		disk;

	v = normalize(*(cone->axis));
	oc = vector_sub(origin, *(cone->apex));
	cos_angle = cos(cone->angle);
	q = cone_shadow_quadratic(dir, oc, v, cos_angle);
	if (q.discriminant < 0.0)
		t_side = -1.0;
	else
		t_side = select_cone_root_shadow(q, dir, oc, cone);
	/* build base disk */
	disk.center = vector_addition(*(cone->apex), vector_scale(v, cone->height));
	disk.normal = v;
	disk.radius = fabs(tan(cone->angle) * cone->height);
	/* check cap shadow */
	t_cap = check_disk_hit_shadow(origin, dir, disk);
	if (t_cap > 0.0 && (t_side < 0.0 || t_cap < t_side))
		return (t_cap);
	return (t_side);
}

static double	select_cone_best_t(t_quad q, t_vector dir, t_vector oc,
		t_cone *cone)
{
	double		t1;
	double		t2;
	double		best_t;
	t_vector	v;

	v = normalize(*(cone->axis));
	t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	best_t = INFINITY;
	if (t1 > 1e-6 && vector_dot(vector_addition(oc, vector_scale(dir, t1)), v)
		>= 0.0 && vector_dot(vector_addition(oc, vector_scale(dir, t1)), v)
		<= cone->height)
		best_t = t1;
	if (t2 > 1e-6 && vector_dot(vector_addition(oc, vector_scale(dir, t2)), v)
		>= 0.0 && vector_dot(vector_addition(oc, vector_scale(dir, t2)), v)
		<= cone->height && t2 < best_t)
		best_t = t2;
	return (best_t);
}

double	intersect_cone(t_camera *cam, t_vector dir, t_cone *cone)
{
	t_vector	oc;
	t_vector	v;
	t_quad		q;
	double		cos_angle;
	double		t_side;
	double		t_cap;
	t_disk		disk;

	v = normalize(*(cone->axis));
	oc = vector_sub(*(cam->position), *(cone->apex));
	cos_angle = cos(cone->angle);
	q = cone_shadow_quadratic(dir, oc, v, cos_angle);
	if (q.discriminant < 0.0)
		t_side = INFINITY;
	else
		t_side = select_cone_best_t(q, dir, oc, cone);
	/* build base disk */
	disk.center = vector_addition(*(cone->apex), vector_scale(v, cone->height));
	disk.normal = v;
	disk.radius = fabs(tan(cone->angle) * cone->height);
	/* check cap hit */
	t_cap = check_disk_hit(cam, dir, disk);
	if (t_cap > 0.0 && t_cap < t_side)
		return (t_cap);
	return (t_side);
}
