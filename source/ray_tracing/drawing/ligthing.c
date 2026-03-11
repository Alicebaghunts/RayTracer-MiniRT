/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ligthing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:55:14 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 13:45:50 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/intersect.h"
#include "../../../includes/rendering.h"

t_color	get_object_color(t_object *obj)
{
	if (!obj || !obj->data)
		return ((t_color){0, 0, 0});
	if (obj->type == 's' && obj->data->sphere)
		return (*(obj->data->sphere->color));
	else if (obj->type == 'p' && obj->data->plane)
		return (*(obj->data->plane->color));
	else if (obj->type == 'c' && obj->data->cylinder)
		return (*(obj->data->cylinder->color));
	else if (obj->type == 'o' && obj->data->cone)
		return (*(obj->data->cone->color));
	return ((t_color){0, 0, 0});
}

static void	add_diffuse(t_light_info *info)
{
	t_vector	light_dir;
	double		diff;

	light_dir = normalize(vector_sub(*(info->light->position),
				info->hit_point));
	diff = fmax(0.0, vector_dot(info->normal, light_dir));
	if (diff > 0.0)
	{
		info->result->red += (int)(info->obj_color.red * info->light->color->red
				/ 255.0 * info->light->brightness_ratio * diff);
		info->result->green += (int)(info->obj_color.green
				* info->light->color->green / 255.0
				* info->light->brightness_ratio * diff);
		info->result->blue += (int)(info->obj_color.blue
				* info->light->color->blue / 255.0
				* info->light->brightness_ratio * diff);
	}
}

static void	add_specular(t_light_info *info)
{
	t_vector		light_dir;
	t_vector		reflect_dir;
	double			spec;
	const double	ks = 0.6;

	light_dir = normalize(vector_sub(*(info->light->position),
				info->hit_point));
	reflect_dir = normalize(vector_sub(vector_scale(info->normal, 2.0
					* vector_dot(info->normal, light_dir)), light_dir));
	spec = pow(fmax(0.0, vector_dot(info->view_dir, reflect_dir)), 10);
	if (spec > 0.0)
	{
		info->result->red += (int)(info->light->color->red * ks
				* info->light->brightness_ratio * spec);
		info->result->green += (int)(info->light->color->green * ks
				* info->light->brightness_ratio * spec);
		info->result->blue += (int)(info->light->color->blue * ks
				* info->light->brightness_ratio * spec);
	}
}

void	add_light_contribution_struct(t_light_info *info)
{
	add_diffuse(info);
	add_specular(info);
}
