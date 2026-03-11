/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_disk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:43:10 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/16 16:30:26 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/intersect.h"

static double	intersect_disk(t_camera *cam, t_vector ray, t_disk disk)
{
	double		denom;
	double		t;
	t_vector	p;

	denom = vector_dot(disk.normal, ray);
	if (fabs(denom) < 1e-6)
		return (-1.0);
	t = vector_dot(vector_sub(disk.center, *(cam->position)), disk.normal)
		/ denom;
	if (t < 1e-6)
		return (-1.0);
	p = vector_addition(*(cam->position), vector_scale(ray, t));
	if (vector_length(vector_sub(p, disk.center)) <= disk.radius)
		return (t);
	return (-1.0);
}

double	check_disk_hit(t_camera *cam, t_vector ray, t_disk disk)
{
	return (intersect_disk(cam, ray, disk));
}

static double	intersect_disk_shadow(t_vector origin, t_vector dir,
		t_disk disk)
{
	double		denom;
	double		t;
	t_vector	p;

	denom = vector_dot(disk.normal, dir);
	if (fabs(denom) < 1e-6)
		return (-1.0);
	t = vector_dot(vector_sub(disk.center, origin), disk.normal) / denom;
	if (t < 1e-6)
		return (-1.0);
	p = vector_addition(origin, vector_scale(dir, t));
	if (vector_length(vector_sub(p, disk.center)) <= disk.radius)
		return (t);
	return (-1.0);
}

double	check_disk_hit_shadow(t_vector origin, t_vector dir, t_disk disk)
{
	return (intersect_disk_shadow(origin, dir, disk));
}
