/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:03:50 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 13:11:18 by alisharu         ###   ########.fr       */
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
	if (uv[0] < 0.0)
		uv[0] += 1.0;
	if (uv[0] > 1.0)
		uv[0] -= 1.0;
	if (uv[1] < 0.0)
		uv[1] = 0.0;
	if (uv[1] > 1.0)
		uv[1] = 1.0;
}

static t_color	read_texture_color(t_texture *tex, double *uv)
{
	int				x;
	int				y;
	unsigned int	pixel;
	t_color			c;

	x = (int)(uv[0] * (tex->width - 1));
	y = (int)(uv[1] * (tex->height - 1));
	pixel = *(unsigned int *)(tex->addr + y * tex->size_line + x * (tex->bpp
				/ 8));
	c.red = (pixel >> 16) & 0xFF;
	c.green = (pixel >> 8) & 0xFF;
	c.blue = pixel & 0xFF;
	return (c);
}

t_color	get_sphere_texture_color(t_sphere *sphere, t_texture *tex,
		t_vector hit_point)
{
	t_vector	n;
	double		uv[2];

	if (!sphere || !tex || !tex->img || !tex->addr || tex->width <= 0
		|| tex->height <= 0)
		return (*(sphere->color));
	n = get_sphere_normal(sphere, hit_point);
	get_sphere_uv(n, uv);
	return (read_texture_color(tex, uv));
}

t_color	get_texture_color_uv(t_texture *tex, double u, double v)
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
