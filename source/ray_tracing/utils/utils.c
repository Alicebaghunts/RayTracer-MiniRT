/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:00:58 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 21:17:58 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

t_render_mode	get_render_mode(t_scene *scene, t_object *obj)
{
	if (scene->selected_object == obj)
		return (scene->selected_mode);
	return (MODE_TEXTURE);
}

int	has_sphere_tex(t_object *obj)
{
	return (obj && obj->type == 's' && obj->data && obj->data->sphere
		&& obj->data->sphere->texture);
}

void	clamp_color(t_color *c)
{
	if (c->red > 255)
		c->red = 255;
	if (c->green > 255)
		c->green = 255;
	if (c->blue > 255)
		c->blue = 255;
}

double	color_to_height(t_color c)
{
	return (((c.red + c.green + c.blue) / 3.0) / 255.0);
}

t_vector	sphere_bitangent(t_vector normal, t_vector tangent)
{
	return (vector_normalize(vector_cross(normal, tangent)));
}
