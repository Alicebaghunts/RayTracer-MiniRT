/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_checkerboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:08:07 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 13:13:38 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

static t_vector	get_sphere_normal(t_sphere *sp, t_vector hit)
{
	return (normalize(vector_sub(hit, *(sp->position))));
}

static void	get_sphere_uv(t_vector n, double *uv)
{
	uv[0] = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	uv[1] = 0.5 - asin(n.y) / M_PI;
}

static t_color	get_checker_color(double *uv)
{
	int	check_u;
	int	check_v;

	check_u = (int)(uv[0] * 10.0);
	check_v = (int)(uv[1] * 10.0);
	if ((check_u + check_v) % 2 == 0)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

t_color	get_sphere_checkerboard(t_sphere *sphere, t_vector hit_point)
{
	t_vector	n;
	double		uv[2];

	n = get_sphere_normal(sphere, hit_point);
	get_sphere_uv(n, uv);
	return (get_checker_color(uv));
}

t_color	get_object_checkerboard(t_object *obj, t_vector hit_point)
{
	if (!obj)
		return (get_object_color(obj));
	if (obj->type == 's' && obj->data && obj->data->sphere)
		return (get_sphere_checkerboard(obj->data->sphere, hit_point));
	if (obj->type == 'p' && obj->data && obj->data->plane)
		return (get_plane_checkerboard(obj->data->plane, hit_point));
	if (obj->type == 'c' && obj->data && obj->data->cylinder)
		return (get_cylinder_checkerboard(obj->data->cylinder, hit_point));
	if (obj->type == 'o' && obj->data && obj->data->cone)
		return (get_cone_checkerboard(obj->data->cone, hit_point));
	return (get_object_color(obj));
}
