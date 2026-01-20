/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_checkerboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:12:30 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 12:12:59 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static t_vector	get_plane_up(t_vector n)
{
	if (fabs(n.y) > 0.999)
		return ((t_vector){1.0, 0.0, 0.0});
	return ((t_vector){0.0, 1.0, 0.0});
}

static void	get_plane_basis(t_vector n, t_vector *t, t_vector *b)
{
	t_vector	up;

	up = get_plane_up(n);
	*t = normalize(vector_cross(n, up));
	*b = normalize(vector_cross(n, *t));
}

static t_color	get_checker_color(double ux, double vy)
{
	int	check_u;
	int	check_v;

	check_u = (int)floor(ux * 1.0);
	check_v = (int)floor(vy * 1.0);
	if ((check_u + check_v) % 2 == 0)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

t_color	get_plane_checkerboard(t_plane *pl, t_vector hit_point)
{
	t_vector	rel;
	t_vector	tb[2];
	double		uv[2];

	rel = vector_sub(hit_point, *(pl->position));
	get_plane_basis(*(pl->normal), &tb[0], &tb[1]);
	uv[0] = vector_dot(rel, tb[0]);
	uv[1] = vector_dot(rel, tb[1]);
	return (get_checker_color(uv[0], uv[1]));
}
