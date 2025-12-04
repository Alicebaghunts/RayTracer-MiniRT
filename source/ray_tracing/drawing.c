/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:05:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/04 20:10:09 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static double	get_intersection(t_object *obj, t_camera *cam, t_vector ray_dir)
{
	t_hit_type	hit_type;
	t_ray_data	data;

	if (obj && obj->type == 's' && obj->data && obj->data->sphere)
		return (intersect_sphere(cam, ray_dir, obj->data->sphere));
	else if (obj && obj->type == 'p' && obj->data && obj->data->plane)
		return (intersect_plane(cam, ray_dir, obj->data->plane));
	else if (obj && obj->type == 'o' && obj->data && obj->data->cone)
		return (intersect_cone(cam, ray_dir, obj->data->cone));
	else if (obj && obj->type == 'c' && obj->data && obj->data->cylinder)
	{
		data.cam = cam;
		data.ray = ray_dir;
		data.cy = obj->data->cylinder;
		return (intersect_cylinder(data, &hit_type));
	}
	return (INFINITY);
}

static t_vector	get_normal(t_object *obj, t_vector hit_point)
{
	if (obj->type == 's')
		return (sphere_normal(obj->data->sphere, hit_point));
	else if (obj->type == 'p')
		return (*(obj->data->plane->normal));
	else if (obj->type == 'o')
		return (cone_normal(obj->data->cone, hit_point));
	return (cylinder_normal(obj->data->cylinder, hit_point));
	return ((t_vector){0, 1, 0});
}

static t_object	*find_closest_object(t_scene *scene, t_camera *cam,
		t_vector ray_dir, double *min_t)
{
	t_list		*node;
	t_object	*obj;
	double		t;
	t_object	*closest;

	*min_t = INFINITY;
	closest = NULL;
	node = scene->objects;
	while (node)
	{
		obj = (t_object *)node->content;
		t = get_intersection(obj, cam, ray_dir);
		if (t > 0.0 && t < *min_t)
		{
			*min_t = t;
			closest = obj;
		}
		node = node->next;
	}
	return (closest);
}

t_vector	sphere_bitangent(t_vector normal, t_vector tangent)
{
	return (vector_normalize(vector_cross(normal, tangent)));
}

static void	draw_pixel(t_mlx *app, t_camera *cam, int x, int y)
{
	t_vector	ray_dir;
	t_hit		hit;
	t_sphere	*sp;
	t_vector	p;
	float		u;
	float		v;
	float		bump;
	t_vector	tangent;
	t_vector	bitangent;
	t_color		shaded;
	int			rgb;

	ray_dir = compute_ray(cam, x, y);
	hit.closest = find_closest_object(app->scene, cam, ray_dir, &hit.min_t);
	if (hit.closest)
	{
		hit.hit_point = vector_addition(*(cam->position), vector_scale(ray_dir,
					hit.min_t));
		hit.normal = get_normal(hit.closest, hit.hit_point);
		if (hit.closest->type == 's' && hit.closest->data->sphere->bump)
		{
			sp = hit.closest->data->sphere;
			p = vector_sub(hit.hit_point, *(sp->position));
			u = 0.5 + atan2(p.z, p.x) / (2 * M_PI);
			v = 0.5 - asin(p.y / (sp->diameter / 2)) / M_PI;
			bump = get_sphere_bump(sp, u, v);
			tangent = sphere_tangent(hit.normal);
			bitangent = sphere_bitangent(hit.normal, tangent);
			hit.normal = apply_sphere_bump(hit.normal, bump, tangent,
					bitangent);
		}
		shaded = shade(app->scene, hit.hit_point, hit.normal, hit.closest);
		rgb = (shaded.red << 16) | (shaded.green << 8) | shaded.blue;
		mlx_pixel_put(app->mlx, app->window, x, y, rgb);
	}
	else
		mlx_pixel_put(app->mlx, app->window, x, y, 0x000000);
}

void	drawing(t_mlx *app)
{
	int			y;
	int			x;
	t_camera	*cam;
	t_list		*cam_node;

	if (!app || !app->scene)
		return ;
	cam_node = app->scene->active_camera;
	if (!cam_node)
		cam_node = app->scene->camera;
	if (!cam_node)
		return ;
	cam = (t_camera *)cam_node->content;
	y = 0;
	while (y < MLX_Y)
	{
		x = 0;
		while (x < MLX_X)
		{
			draw_pixel(app, cam, x, y);
			x++;
		}
		y++;
	}
}
