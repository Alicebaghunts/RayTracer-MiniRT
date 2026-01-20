/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:05:03 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 21:17:49 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

t_color	compute_ambient(t_scene *scene, t_color obj_color)
{
	t_color	result;

	result.red = (int)(obj_color.red * scene->ambient->color->red / 255.0
			* scene->ambient->light_ratio);
	result.green = (int)(obj_color.green * scene->ambient->color->green / 255.0
			* scene->ambient->light_ratio);
	result.blue = (int)(obj_color.blue * scene->ambient->color->blue / 255.0
			* scene->ambient->light_ratio);
	return (result);
}

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

t_vector	get_normal(t_object *obj, t_vector hit_point)
{
	if (obj->type == 's')
		return (sphere_normal(obj->data->sphere, hit_point));
	else if (obj->type == 'p')
		return (*(obj->data->plane->normal));
	else if (obj->type == 'o')
		return (cone_normal(obj->data->cone, hit_point));
	return (cylinder_normal(obj->data->cylinder, hit_point));
}

t_object	*find_closest_object(t_scene *scene, t_camera *cam,
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

void	drawing(t_mlx *app)
{
	if (!app || !app->scene)
		return ;
	start_render_threads(app);
}
