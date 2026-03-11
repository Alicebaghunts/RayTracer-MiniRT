/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:57:27 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/24 16:54:36 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/initialization.h"

double	vector_length(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

t_vector	sphere_normal(t_sphere *sphere, t_vector hit_point)
{
	t_vector	normal;

	normal.x = hit_point.x - sphere->position->x;
	normal.y = hit_point.y - sphere->position->y;
	normal.z = hit_point.z - sphere->position->z;
	return (normalize(normal));
}
