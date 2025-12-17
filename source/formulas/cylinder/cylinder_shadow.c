/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shadow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:12:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/16 16:30:50 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

static t_quad	cylinder_shadow_quadratic(t_vector dir, t_vector oc,
		t_vector axis, double radius)
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

static double	select_cylinder_root(double a, double b, double disc)
{
	double	t1;
	double	t2;

	if (disc < 0)
		return (-1.0);
	t1 = (-b - sqrt(disc)) / (2.0 * a);
	t2 = (-b + sqrt(disc)) / (2.0 * a);
	if (t1 > 1e-6)
		return (t1);
	if (t2 > 1e-6)
		return (t2);
	return (-1.0);
}

static int	cylinder_shadow_valid(t_vector hit, t_cylinder *cy, t_vector axis)
{
	t_vector	base_to_hit;
	double		dist;

	base_to_hit = vector_sub(hit, *(cy->position));
	dist = vector_dot(base_to_hit, axis);
	return (fabs(dist) <= cy->height / 2.0);
}

double	intersect_cylinder_shadow(t_vector origin, t_vector dir, t_cylinder *cy)
{
	t_vector	oc;
	t_vector	axis;
	t_quad		q;
	double		t;
	t_vector	hit;
	double		t_top;
	double		t_bottom;
	t_disk		top_disk;
	t_disk		bottom_disk;

	oc = vector_sub(origin, *(cy->position));
	axis = normalize(*(cy->direction));
	q = cylinder_shadow_quadratic(dir, oc, axis, cy->diameter / 2.0);
	t = select_cylinder_root(q.a, q.b, q.discriminant);
	if (t > 1e-6)
	{
		hit = vector_addition(origin, vector_scale(dir, t));
		if (!cylinder_shadow_valid(hit, cy, axis))
			t = -1.0;
	}
	top_disk.center = vector_addition(*(cy->position), vector_scale(axis,
				cy->height / 2.0));
	top_disk.normal = axis;
	top_disk.radius = cy->diameter / 2.0;
	bottom_disk.center = vector_sub(*(cy->position), vector_scale(axis,
				cy->height / 2.0));
	bottom_disk.normal = vector_scale(axis, -1);
	bottom_disk.radius = cy->diameter / 2.0;
	t_top = check_disk_hit_shadow(origin, dir, top_disk);
	t_bottom = check_disk_hit_shadow(origin, dir, bottom_disk);
	if (t < 0.0 || (t_top >= 0.0 && t_top < t))
		t = t_top;
	if (t < 0.0 || (t_bottom >= 0.0 && (t < 0.0 || t_bottom < t)))
		t = t_bottom;
	return (t);
}
