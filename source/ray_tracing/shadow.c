/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:17:47 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/16 16:31:48 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "rendering.h"

static int	check_shadow_hit(t_object *obj, t_vector origin, t_vector dir,
		double light_dist)
{
	double	t;

	if (obj->type == 's')
		t = intersect_sphere_shadow(origin, dir, obj->data->sphere);
	else if (obj->type == 'p')
		t = intersect_plane_shadow(origin, dir, obj->data->plane);
	else if (obj->type == 'c')
		t = intersect_cylinder_shadow(origin, dir, obj->data->cylinder);
	else if (obj->type == 'o')
		t = intersect_cone_shadow(origin, dir, obj->data->cone);
	else
		return (0);
	return (t > 1e-6 && t < light_dist);
}

int	in_shadow(t_shadow_info info)
{
	t_list			*node;
	t_object		*obj;
	t_vector		shadow_origin;
	const double	epsilon = 5e-4;

	shadow_origin = vector_addition(info.hit_point, vector_scale(info.normal,
				epsilon));
	info.light_dir = normalize(info.light_dir);
	node = info.scene->objects;
	while (node)
	{
		obj = (t_object *)node->content;
		if (obj != info.ignore && check_shadow_hit(obj, shadow_origin,
				info.light_dir, info.light_dist))
			return (1);
		node = node->next;
	}
	return (0);
}
