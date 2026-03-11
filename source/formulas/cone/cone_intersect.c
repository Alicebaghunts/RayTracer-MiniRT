/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:44:36 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 17:40:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/intersect.h"
#include "../../../includes/rendering.h"

static double	cone_height_at_t(t_vector oc, t_vector dir, double t,
	t_vector v)
{
	return (vector_dot(vector_addition(oc, vector_scale(dir, t)), v));
}

double	select_cone_root(t_quad q, t_vector dir, t_vector oc,
		t_cone *cone)
{
	double	t1;
	double	t2;
	double	best;

	t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	best = -1.0;
	if (t1 > 1e-6 && cone_height_at_t(oc, dir, t1, normalize(*(cone->axis)))
		>= 0.0 && cone_height_at_t(oc, dir, t1, normalize(*(cone->axis)))
		<= cone->height)
		best = t1;
	if (t2 > 1e-6 && cone_height_at_t(oc, dir, t2, normalize(*(cone->axis)))
		>= 0.0 && cone_height_at_t(oc, dir, t2, normalize(*(cone->axis)))
		<= cone->height && (best < 0.0 || t2 < best))
		best = t2;
	return (best);
}

static double	select_cone_root_inf(t_quad q, t_vector dir, t_vector oc,
		t_cone *cone)
{
	double	t;
	double	best;

	best = INFINITY;
	t = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	if (t > 1e-6 && cone_height_at_t(oc, dir, t, normalize(*(cone->axis)))
		>= 0.0 && cone_height_at_t(oc, dir, t, normalize(*(cone->axis)))
		<= cone->height)
		best = t;
	t = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	if (t > 1e-6 && cone_height_at_t(oc, dir, t, normalize(*(cone->axis)))
		>= 0.0 && cone_height_at_t(oc, dir, t, normalize(*(cone->axis)))
		<= cone->height && t < best)
		best = t;
	return (best);
}

static double	cone_side_hit(t_camera *cam, t_vector dir, t_cone *cone)
{
	t_vector	oc;
	t_vector	v;
	t_quad		q;
	double		ca;

	v = normalize(*(cone->axis));
	oc = vector_sub(*(cam->position), *(cone->apex));
	ca = cos(cone->angle);
	q = cone_quadratic(dir, oc, v, ca);
	if (q.discriminant < 0.0)
		return (INFINITY);
	return (select_cone_root_inf(q, dir, oc, cone));
}

double	intersect_cone(t_camera *cam, t_vector dir, t_cone *cone)
{
	t_vector	v;
	t_disk		disk;
	double		t[2];

	v = normalize(*(cone->axis));
	t[0] = cone_side_hit(cam, dir, cone);
	disk = cone_base_disk(cone, v);
	t[1] = check_disk_hit(cam, dir, disk);
	if (t[1] > 0.0 && t[1] < t[0])
		return (t[1]);
	return (t[0]);
}
