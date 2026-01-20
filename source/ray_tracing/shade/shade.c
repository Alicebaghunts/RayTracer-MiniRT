/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:50:25 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 12:02:18 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "rendering.h"
#include "shade_helpers.h"

static t_color	get_obj_color(t_render_mode mode, t_object *obj,
		t_vector hit_point)
{
	if (mode == MODE_CHECKERBOARD)
		return (get_object_checkerboard(obj, hit_point));
	if (mode == MODE_TEXTURE && has_sphere_tex(obj))
		return (get_sphere_texture_color(obj->data->sphere,
				obj->data->sphere->texture, hit_point));
	if (mode == MODE_BUMP)
		return (get_object_color(obj));
	if (has_sphere_tex(obj))
		return (get_sphere_texture_color(obj->data->sphere,
				obj->data->sphere->texture, hit_point));
	return (get_object_color(obj));
}

static int	set_view_dir(t_scene *scene, t_vector hit_point, t_vector *view_dir)
{
	t_list		*cam_node;
	t_camera	*cam;

	cam_node = scene->active_camera;
	if (!cam_node)
		cam_node = scene->camera;
	if (!cam_node)
		return (0);
	cam = (t_camera *)cam_node->content;
	*view_dir = normalize(vector_sub(*(cam->position), hit_point));
	return (1);
}

static t_vector	get_final_normal(t_object *obj, t_vector hit_point,
		t_vector normal)
{
	if (obj && obj->type == 's' && obj->data && obj->data->sphere
		&& obj->data->sphere->bump)
		return (get_sphere_bump_normal(obj->data->sphere,
				obj->data->sphere->bump, hit_point, normal));
	if (obj && obj->type != 's' && obj->data && obj->data->sphere
		&& obj->data->sphere->bump)
		return (get_object_bump_normal(obj, obj->data->sphere->bump, hit_point,
				normal));
	return (normal);
}

static t_vector	flip_normal_if_needed(t_vector view_dir, t_vector n)
{
	if (vector_dot(view_dir, n) < 0.0)
		return (vector_scale(n, -1.0));
	return (n);
}

t_color	shade(t_scene *scene, t_vector hit_point, t_vector normal,
		t_object *obj)
{
	t_shade_info	info;
	t_color			result;

	info.scene = scene;
	info.hit_point = hit_point;
	info.obj = obj;
	info.obj_color = get_obj_color(get_render_mode(scene, obj), obj, hit_point);
	if (!set_view_dir(scene, hit_point, &info.view_dir))
		return ((t_color){0, 0, 0});
	info.normal = flip_normal_if_needed(info.view_dir, get_final_normal(obj,
				hit_point, normal));
	result = compute_ambient(scene, info.obj_color);
	info.result = &result;
	compute_lights(info);
	clamp_color(&result);
	return (result);
}
