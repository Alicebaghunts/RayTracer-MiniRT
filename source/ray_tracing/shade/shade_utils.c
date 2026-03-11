/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:03:13 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 13:32:40 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shade_utils.h"

void	init_light_info_base(t_light_info *li, t_shade_info *si, t_light *light)
{
	li->result = si->result;
	li->obj_color = si->obj_color;
	li->light = light;
	li->normal = si->normal;
}

t_vector	get_object_bump_normal(t_object *obj, t_texture *bump,
		t_vector hit_point, t_vector normal)
{
	if (obj->type == 's' && obj->data && obj->data->sphere)
		return (get_sphere_bump_normal(obj->data->sphere, bump, hit_point,
				normal));
	return (normal);
}

t_color	determine_obj_color(t_scene *scene, t_object *obj, t_vector hit_point)
{
	t_color			obj_color;
	t_render_mode	mode;

	if (scene->selected_object == obj)
		mode = scene->selected_mode;
	else
		mode = MODE_TEXTURE;
	if (mode == MODE_CHECKERBOARD)
		obj_color = get_object_checkerboard(obj, hit_point);
	else if (mode == MODE_TEXTURE && obj && obj->type == 's' && obj->data
		&& obj->data->sphere && obj->data->sphere->texture)
		obj_color = get_sphere_texture_color(obj->data->sphere,
				obj->data->sphere->texture, hit_point);
	else if (mode == MODE_BUMP)
		obj_color = get_object_color(obj);
	else if (obj && obj->type == 's' && obj->data && obj->data->sphere
		&& obj->data->sphere->texture)
		obj_color = get_sphere_texture_color(obj->data->sphere,
				obj->data->sphere->texture, hit_point);
	else
		obj_color = get_object_color(obj);
	return (obj_color);
}

t_vector	compute_final_normal(t_scene *scene, t_object *obj,
		t_vector hit_point, t_vector normal)
{
	t_vector	final_normal;

	(void)scene;
	final_normal = normal;
	if (obj && obj->type == 's' && obj->data && obj->data->sphere
		&& obj->data->sphere->bump)
	{
		final_normal = get_sphere_bump_normal(obj->data->sphere,
				obj->data->sphere->bump, hit_point, normal);
	}
	else if (obj && obj->type != 's' && obj->data && obj->data->sphere
		&& obj->data->sphere->bump)
	{
		final_normal = get_object_bump_normal(obj, obj->data->sphere->bump,
				hit_point, normal);
	}
	return (final_normal);
}

void	compute_lights(t_shade_info info)
{
	t_list			*l_node;
	t_light			*light;
	t_shadow_info	shadow;
	t_light_info	light_info;

	l_node = info.scene->lights;
	while (l_node)
	{
		light = (t_light *)l_node->content;
		shadow.scene = info.scene;
		shadow.hit_point = info.hit_point;
		shadow.normal = info.normal;
		shadow.light_dir = vector_sub(*(light->position), info.hit_point);
		shadow.light_dist = vector_length(shadow.light_dir);
		shadow.ignore = info.obj;
		if (!in_shadow(shadow))
		{
			init_light_info_base(&light_info, &info, light);
			light_info.view_dir = info.view_dir;
			light_info.hit_point = info.hit_point;
			add_light_contribution_struct(&light_info);
		}
		l_node = l_node->next;
	}
}
