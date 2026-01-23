/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:55:25 by alisharu          #+#    #+#             */
/*   Updated: 2026/01/23 11:17:45 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "object_types.h"
# include <math.h>

/* ------------------ Vectors ----------------------- */
t_vector	vector_sub(t_vector a, t_vector b);
t_vector	vector_scale(t_vector a, double s);
t_vector	vector_cross(t_vector a, t_vector b);
t_vector	vector_addition(t_vector a, t_vector b);
t_vector	vector_normalize(t_vector v);
double		vector_length(t_vector v);
double		vector_dot(t_vector a, t_vector b);

#endif
