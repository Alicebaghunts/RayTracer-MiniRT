/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:16:58 by alisharu          #+#    #+#             */
/*   Updated: 2025/12/04 20:09:35 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include <math.h>

float get_sphere_bump(t_sphere *sp, float u, float v)
{
    if (!sp->bump || !sp->bump->addr)
        return 0.5f;
    int x = (int)(u * sp->bump->width) % sp->bump->width;
    int y = (int)(v * sp->bump->height) % sp->bump->height;
    char *pixel = sp->bump->addr + (y * sp->bump->size_line + x * (sp->bump->bpp / 8));
    unsigned char gray = pixel[0];
    return gray / 255.0f;
}

t_vector sphere_tangent(t_vector normal)
{
    t_vector up = {0, 1, 0};
    if (fabs(normal.y) > 0.99)
        up = (t_vector){1, 0, 0};
    t_vector tangent = vector_normalize(vector_cross(up, normal));
    return tangent;
}

t_vector apply_sphere_bump(t_vector normal, float bump_value, t_vector tangent)
{
    float intensity = (bump_value - 0.5f) * 2.0f;
    float bump_strength = 0.3f;
    t_vector shift = vector_scale(tangent, intensity * bump_strength);
    t_vector new_normal = vector_addition(normal, shift);
    return vector_normalize(new_normal);
}
