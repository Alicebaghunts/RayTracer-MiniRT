/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:32:49 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/24 16:49:34 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/intersect.h"

static t_roots	sphere_roots(t_vector oc, t_vector dir, double radius)
{
	t_roots	r;
	double	a;
	double	b;
	double	c;
	double	disc;

	a = vector_dot(dir, dir);
	b = 2.0 * vector_dot(dir, oc);
	c = vector_dot(oc, oc) - radius * radius;
	disc = b * b - 4 * a * c;
	r.valid = (disc >= 0);
	if (!r.valid)
		return (r);
	r.t1 = (-b - sqrt(disc)) / (2.0 * a);
	r.t2 = (-b + sqrt(disc)) / (2.0 * a);
	return (r);
}

double	intersect_sphere(t_camera *cam, t_vector dir, t_sphere *sp)
{
	t_vector	oc;
	t_roots		r;

	oc = vector_sub(*cam->position, *(sp->position));
	r = sphere_roots(oc, dir, sp->diameter / 2.0);
	if (!r.valid)
		return (INFINITY);
	if (r.t1 > 1e-6 && r.t1 < r.t2)
		return (r.t1);
	if (r.t2 > 1e-6)
		return (r.t2);
	return (INFINITY);
}
