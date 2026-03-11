/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:45:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/10/01 14:05:50 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

double	intersect_plane(t_camera *camera, t_vector ray_dir, t_plane *plane)
{
	double		t;
	t_vector	oc;
	double		denom;

	oc = vector_sub(*(camera->position), *(plane->position));
	denom = vector_dot(ray_dir, *(plane->normal));
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	t = -vector_dot(oc, *(plane->normal)) / denom;
	if (t > 0)
		return (t);
	return (INFINITY);
}
