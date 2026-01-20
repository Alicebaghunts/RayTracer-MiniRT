/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:09:28 by alisharu          #+#    #+#             */
/*   Updated: 2025/09/27 17:59:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static t_quad	calc_sphere_quadratic(t_vector origin, t_vector dir,
		t_sphere *sphere)
{
	t_quad		q;
	t_vector	oc;
	double		radius;

	oc = vector_sub(origin, *(sphere->position));
	radius = sphere->diameter / 2.0;
	q.a = vector_dot(dir, dir);
	q.b = 2.0 * vector_dot(oc, dir);
	q.c = vector_dot(oc, oc) - radius * radius;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	return (q);
}

double	intersect_sphere_shadow(t_vector origin, t_vector dir, t_sphere *sphere)
{
	t_quad	q;
	double	t1;
	double	t2;

	q = calc_sphere_quadratic(origin, dir, sphere);
	if (q.discriminant < 0)
		return (-1.0);
	t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	if (t1 > 1e-10)
		return (t1);
	if (t2 > 1e-10)
		return (t2);
	return (-1.0);
}

double	intersect_plane_shadow(t_vector origin, t_vector dir, t_plane *plane)
{
	double	denom;
	double	t;

	denom = vector_dot(*(plane->normal), dir);
	if (fabs(denom) < 1e-6)
		return (-1.0);
	t = vector_dot(vector_sub(*(plane->position), origin), *(plane->normal))
		/ denom;
	if (t > 1e-6)
		return (t);
	return (-1.0);
}
