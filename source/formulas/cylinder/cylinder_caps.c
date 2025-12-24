/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:05:15 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/24 16:38:43 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#define EPSILON 1e-6

t_vector	get_cylinder_normal(t_cylinder *cy, t_vector hit)
{
	t_vector	axis;
	t_vector	rel;
	double		proj;

	axis = normalize(*(cy->direction));
	rel = vector_sub(hit, *(cy->position));
	proj = vector_dot(rel, axis);
	if (fabs(proj - (cy->height / 2.0)) <= 1e-4)
		return (axis);
	if (fabs(proj + (cy->height / 2.0)) <= 1e-4)
		return (vector_scale(axis, -1));
	return (normalize(vector_sub(rel, vector_scale(axis, vector_dot(rel,
						axis)))));
}

int	check_cylinder_height(t_vector hit, t_cylinder *cy, t_vector axis)
{
	t_vector	center_to_hit;
	double		dist_along_axis;

	center_to_hit = vector_sub(hit, *(cy->position));
	dist_along_axis = vector_dot(center_to_hit, axis);
	return (fabs(dist_along_axis) <= (cy->height / 2.0) + EPSILON);
}

static t_vector	get_cyl_center(t_cylinder *cy, t_vector axis, int top)
{
	if (top)
		return (vector_addition(*(cy->position), vector_scale(axis, cy->height
					/ 2.0)));
	return (vector_sub(*(cy->position), vector_scale(axis, cy->height / 2.0)));
}

double	intersect_cylinder_caps(t_ray_data data, t_hit_type *hit_type)
{
	t_vector	axis;
	t_disk		top_disk;
	t_disk		bottom_disk;
	double		t_top;
	double		t_bottom;

	axis = normalize(*(data.cy->direction));
	top_disk.center = get_cyl_center(data.cy, axis, 1);
	top_disk.normal = axis;
	top_disk.radius = data.cy->diameter / 2.0;
	bottom_disk.center = get_cyl_center(data.cy, axis, 0);
	bottom_disk.normal = vector_scale(axis, -1);
	bottom_disk.radius = data.cy->diameter / 2.0;
	t_top = check_disk_hit(data.cam, data.ray, top_disk);
	t_bottom = check_disk_hit(data.cam, data.ray, bottom_disk);
	if (t_top < 0.0 && t_bottom < 0.0)
		return (-1.0);
	if (t_top < 0.0 || (t_bottom >= 0.0 && t_bottom < t_top))
	{
		*hit_type = HIT_CYLINDER_BOTTOM;
		return (t_bottom);
	}
	*hit_type = HIT_CYLINDER_TOP;
	return (t_top);
}
