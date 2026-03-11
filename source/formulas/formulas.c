/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:13:20 by alisharu          #+#    #+#             */
/*   Updated: 2025/09/28 18:44:31 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rendering.h"

static void	cam_basis(t_camera *cam, t_vector *right, t_vector *up)
{
	t_vector	world_up;

	world_up = (t_vector){0, 1, 0};
	if (fabs(cam->direction->x) < 1e-6 && fabs(cam->direction->z) < 1e-6)
		world_up = (t_vector){0, 0, 1};
	*right = normalize(vector_cross(*(cam->direction), world_up));
	*up = normalize(vector_cross(*right, *(cam->direction)));
}

t_vector	compute_ray(t_camera *cam, double px, double py)
{
	t_rayinfo	r;
	t_vector	right;
	t_vector	up;
	t_vector	dir;

	r.aspect = (double)MLX_X / (double)MLX_Y;
	r.scale = tan(cam->field_of_view * M_PI / 180.0 / 2.0);
	r.sx = (2.0 * (px + 0.5) / MLX_X - 1.0) * r.aspect * r.scale;
	r.sy = (1.0 - 2.0 * (py + 0.5) / MLX_Y) * r.scale;
	cam_basis(cam, &right, &up);
	dir = vector_addition(
			vector_addition(*(cam->direction), vector_scale(right, r.sx)),
			vector_scale(up, r.sy));
	return (normalize(dir));
}
