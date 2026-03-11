/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:10:39 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/20 21:31:13 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

static t_vector	get_up_axis(t_vector axis)
{
	if (fabs(axis.y) > 0.999)
		return ((t_vector){1.0, 0.0, 0.0});
	return ((t_vector){0.0, 1.0, 0.0});
}

void	get_cy_basis(t_vector axis, t_vector *t, t_vector *b)
{
	t_vector	up;

	up = get_up_axis(axis);
	*t = normalize(vector_cross(up, axis));
	*b = normalize(vector_cross(axis, *t));
}
