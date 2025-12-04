/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:50:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/02 17:31:39 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "rendering.h"

static t_color	get_sphere_texture_color(t_sphere *sphere, t_texture *tex,
		t_vector hit_point)
{
	t_vector	rel;
	t_vector	n;
	double		u;
	double		v;
	int			x;
	int			y;
	unsigned int	pixel;
	t_color		color;

	if (!sphere || !tex || !tex->img || !tex->addr || tex->width <= 0
		|| tex->height <= 0)
		return (*(sphere->color));
	rel = vector_sub(hit_point, *(sphere->position));
	n = normalize(rel);
	u = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	if (u < 0.0)
		u += 1.0;
	if (u > 1.0)
		u -= 1.0;
	if (v < 0.0)
		v = 0.0;
	if (v > 1.0)
		v = 1.0;
	x = (int)(u * (tex->width - 1));
	y = (int)(v * (tex->height - 1));
	pixel = *(unsigned int *)(tex->addr + y * tex->size_line
			+ x * (tex->bpp / 8));
	color.red = (pixel >> 16) & 0xFF;
	color.green = (pixel >> 8) & 0xFF;
	color.blue = pixel & 0xFF;
	return (color);
}

static t_vector	get_sphere_bump_normal(t_sphere *sphere, t_texture *bump,
		t_vector hit_point, t_vector geom_normal)
{
	t_vector	rel;
	t_vector	n;
	double		u;
	double		v;
	int			x;
	int			y;
	unsigned int	pixel;
	double		nx;
	double		ny;
	double		nz;
	t_vector	tangent;
	t_vector	bitangent;
	t_vector	tspace;
	t_vector	world;
	t_vector	up;

	if (!sphere || !bump || !bump->img || !bump->addr
		|| bump->width <= 0 || bump->height <= 0)
		return (geom_normal);
	rel = vector_sub(hit_point, *(sphere->position));
	n = normalize(rel);
	u = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	if (u < 0.0)
		u += 1.0;
	if (u > 1.0)
		u -= 1.0;
	if (v < 0.0)
		v = 0.0;
	if (v > 1.0)
		v = 1.0;
	x = (int)(u * (bump->width - 1));
	y = (int)(v * (bump->height - 1));
	pixel = *(unsigned int *)(bump->addr + y * bump->size_line
			+ x * (bump->bpp / 8));
	nx = ((pixel >> 16) & 0xFF) / 255.0 * 2.0 - 1.0;
	ny = ((pixel >> 8) & 0xFF) / 255.0 * 2.0 - 1.0;
	nz = (pixel & 0xFF) / 255.0 * 2.0 - 1.0;
	tspace.x = nx;
	tspace.y = ny;
	tspace.z = nz;
	if (fabs(n.y) > 0.999)
		up = (t_vector){1.0, 0.0, 0.0};
	else
		up = (t_vector){0.0, 1.0, 0.0};
	tangent = normalize(vector_cross(up, n));
	bitangent = normalize(vector_cross(n, tangent));
	world = vector_addition(
			vector_addition(vector_scale(tangent, tspace.x),
				vector_scale(bitangent, tspace.y)),
			vector_scale(n, tspace.z));
	return (normalize(world));
}

static void	init_light_info_base(t_light_info *li, t_shade_info *si,
		t_light *light)
{
	li->result = si->result;
	li->obj_color = si->obj_color;
	li->light = light;
	li->normal = si->normal;
}

static void	compute_lights(t_shade_info info)
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

t_color	shade(t_scene *scene, t_vector hit_point, t_vector normal,
		t_object *obj)
{
	t_color			result;
	t_color			obj_color;
	t_camera		*cam;
	t_list			*cam_node;
	t_vector		view_dir;
	t_vector		final_normal;
	t_shade_info	info;

	if (obj && obj->type == 's' && obj->data && obj->data->sphere
		&& obj->data->sphere->texture)
		obj_color = get_sphere_texture_color(obj->data->sphere,
				obj->data->sphere->texture, hit_point);
	else
		obj_color = get_object_color(obj);
	cam_node = scene->active_camera;
	if (!cam_node)
		cam_node = scene->camera;
	if (!cam_node)
		return ((t_color){0, 0, 0});
	cam = (t_camera *)cam_node->content;
	view_dir = normalize(vector_sub(*(cam->position), hit_point));
	final_normal = normal;
	if (obj && obj->type == 's' && obj->data && obj->data->sphere
		&& obj->data->sphere->bump)
		final_normal = get_sphere_bump_normal(obj->data->sphere,
				obj->data->sphere->bump, hit_point, normal);
	result = compute_ambient(scene, obj_color);
	info.scene = scene;
	info.hit_point = hit_point;
	info.normal = final_normal;
	info.view_dir = view_dir;
	info.obj = obj;
	info.obj_color = obj_color;
	info.result = &result;
	compute_lights(info);
	if (result.red > 255)
		result.red = 255;
	if (result.green > 255)
		result.green = 255;
	if (result.blue > 255)
		result.blue = 255;
	return (result);
}
