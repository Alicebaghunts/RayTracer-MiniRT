/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:50:25 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/16 20:31:43 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "rendering.h"

static t_color	get_sphere_texture_color(t_sphere *sphere, t_texture *tex,
		t_vector hit_point)
{
	t_vector		rel;
	t_vector		n;
	double			u;
	double			v;
	int				x;
	int				y;
	unsigned int	pixel;
	t_color			color;

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
	pixel = *(unsigned int *)(tex->addr + y * tex->size_line + x * (tex->bpp
				/ 8));
	color.red = (pixel >> 16) & 0xFF;
	color.green = (pixel >> 8) & 0xFF;
	color.blue = pixel & 0xFF;
	return (color);
}

static t_color	get_sphere_checkerboard(t_sphere *sphere, t_vector hit_point)
{
	t_vector	rel;
	t_vector	n;
	double		u;
	double		v;
	double		check_size;
	int			check_u;
	int			check_v;
	t_color		color1;
	t_color		color2;

	rel = vector_sub(hit_point, *(sphere->position));
	n = normalize(rel);
	u = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	check_size = 10.0;
	check_u = (int)(u * check_size);
	check_v = (int)(v * check_size);
	if ((check_u + check_v) % 2 == 0)
	{
		color1 = (t_color){255, 255, 255};
		return (color1);
	}
	else
	{
		color2 = (t_color){0, 0, 0};
		return (color2);
	}
}

static double	color_to_height(t_color c)
{
	return (((c.red + c.green + c.blue) / 3.0) / 255.0);
}

static t_color	get_texture_color_uv(t_texture *tex, double u, double v)
{
	int				x;
	int				y;
	unsigned int	pixel;
	t_color			color;

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
	pixel = *(unsigned int *)(tex->addr + y * tex->size_line + x * (tex->bpp
				/ 8));
	color.red = (pixel >> 16) & 0xFF;
	color.green = (pixel >> 8) & 0xFF;
	color.blue = pixel & 0xFF;
	return (color);
}

t_vector	get_sphere_bump_normal(t_sphere *sphere, t_texture *bump,
		t_vector hit_point, t_vector normal)
{
	t_vector	n;
	t_vector	rel;
	t_vector	tangent;
	t_vector	bitangent;
	t_vector	up;
	double		strength;
	t_vector	bump_offset;

	double u, v;
	double du, dv;
	double h, h_u, h_v;
	strength = 3;
	if (!sphere || !bump || !bump->addr)
		return (normal);
	rel = vector_sub(hit_point, *(sphere->position));
	n = normalize(rel);
	u = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	du = 1.0 / bump->width;
	dv = 1.0 / bump->height;
	h = color_to_height(get_texture_color_uv(bump, u, v));
	h_u = color_to_height(get_texture_color_uv(bump, u + du, v));
	h_v = color_to_height(get_texture_color_uv(bump, u, v + dv));
	up = (fabs(n.y) > 0.999) ? (t_vector){1, 0, 0} : (t_vector){0, 1, 0};
	tangent = normalize(vector_cross(n, up));
	bitangent = normalize(vector_cross(tangent, n));
	bump_offset = vector_addition(vector_scale(tangent, (h_u - h) * strength),
			vector_scale(bitangent, (h_v - h) * strength));
	return (normalize(vector_addition(n, bump_offset)));
}

static void	init_light_info_base(t_light_info *li, t_shade_info *si,
		t_light *light)
{
	li->result = si->result;
	li->obj_color = si->obj_color;
	li->light = light;
	li->normal = si->normal;
}

static t_color	get_plane_checkerboard(t_plane *pl, t_vector hit_point)
{
	t_vector	rel;
	t_vector	up;
	t_vector	tangent;
	t_vector	bitangent;
	double		ux;
	double		vy;
	double		check_size;
	int			check_u;
	int			check_v;
	t_color		c1;
	t_color		c2;

	rel = vector_sub(hit_point, *(pl->position));
	if (fabs(pl->normal->y) > 0.999)
		up = (t_vector){1.0, 0.0, 0.0};
	else
		up = (t_vector){0.0, 1.0, 0.0};
	tangent = normalize(vector_cross(*pl->normal, up));
	bitangent = normalize(vector_cross(*pl->normal, tangent));
	ux = vector_dot(rel, tangent);
	vy = vector_dot(rel, bitangent);
	check_size = 1.0; /* world units */
	check_u = (int)floor(ux * check_size);
	check_v = (int)floor(vy * check_size);
	if ((check_u + check_v) % 2 == 0)
	{
		c1 = (t_color){255, 255, 255};
		return (c1);
	}
	c2 = (t_color){0, 0, 0};
	return (c2);
}

static t_color	get_cylinder_checkerboard(t_cylinder *cy, t_vector hit_point)
{
	t_vector	rel;
	t_vector	axis;
	t_vector	up;
	t_vector	tangent;
	t_vector	bitangent;
	double		ang;
	double		v;
	double		check_size;
	int			check_u;
	int			check_v;
	t_color		c1;
	t_color		c2;
	double		x;
	double		z;

	axis = normalize(*(cy->direction));
	rel = vector_sub(hit_point, *(cy->position));
	if (fabs(axis.y) > 0.999)
		up = (t_vector){1.0, 0.0, 0.0};
	else
		up = (t_vector){0.0, 1.0, 0.0};
	tangent = normalize(vector_cross(up, axis));
	bitangent = normalize(vector_cross(axis, tangent));
	x = vector_dot(rel, tangent);
	z = vector_dot(rel, bitangent);
	ang = atan2(z, x);
	ang = (ang < 0.0) ? ang + 2.0 * M_PI : ang;
	v = vector_dot(rel, axis);
	check_size = 10.0;
	check_u = (int)floor((ang / (2.0 * M_PI)) * check_size);
	check_v = (int)floor(v * (check_size
				/ (cy->height > 0 ? cy->height : 1.0)));
	if ((check_u + check_v) % 2 == 0)
	{
		c1 = (t_color){255, 255, 255};
		return (c1);
	}
	c2 = (t_color){0, 0, 0};
	return (c2);
}

static t_color	get_cone_checkerboard(t_cone *cone, t_vector hit_point)
{
	t_vector	rel;
	t_vector	axis;
	t_vector	up;
	t_vector	tangent;
	t_vector	bitangent;
	double		ang;
	double		v;
	double		check_size;
	int			check_u;
	int			check_v;
	t_color		c1;
	t_color		c2;
	double		x;
	double		z;

	axis = normalize(*(cone->axis));
	rel = vector_sub(hit_point, *(cone->apex));
	if (fabs(axis.y) > 0.999)
		up = (t_vector){1.0, 0.0, 0.0};
	else
		up = (t_vector){0.0, 1.0, 0.0};
	tangent = normalize(vector_cross(up, axis));
	bitangent = normalize(vector_cross(axis, tangent));
	x = vector_dot(rel, tangent);
	z = vector_dot(rel, bitangent);
	ang = atan2(z, x);
	ang = (ang < 0.0) ? ang + 2.0 * M_PI : ang;
	v = vector_dot(rel, axis); /* distance from apex along axis */
	check_size = 10.0;
	check_u = (int)floor((ang / (2.0 * M_PI)) * check_size);
	check_v = (int)floor(v * (check_size
				/ (cone->height > 0 ? cone->height : 1.0)));
	if ((check_u + check_v) % 2 == 0)
	{
		c1 = (t_color){255, 255, 255};
		return (c1);
	}
	c2 = (t_color){0, 0, 0};
	return (c2);
}

static t_color	get_object_checkerboard(t_object *obj, t_vector hit_point)
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

t_vector	get_object_bump_normal(t_object *obj, t_texture *bump,
		t_vector hit_point, t_vector normal)
{
	if (obj->type == 's' && obj->data && obj->data->sphere)
		return (get_sphere_bump_normal(obj->data->sphere, bump, hit_point,
				normal));
	return (normal);
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
	if (vector_dot(view_dir, final_normal) < 0.0)
		final_normal = vector_scale(final_normal, -1.0);
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
