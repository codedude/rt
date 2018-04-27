/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/27 14:25:21 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "ft_math.h"
#include "vec.h"

static t_float	c[3];

void			matrix_init_value(void)
{
	c[0] = ft_cos(180.0);
	c[1] = 1. - c[0];
	c[2] = ft_sin(180.0);
}

void			matrix_rot_vec(t_vec matrix[3], t_vec v)
{
	t_vec	tmp;

	tmp = v * c[1];
	matrix[0][0] = c[0] + v[0] * tmp[0];
	matrix[1][0] = v[0] * tmp[1] - v[2] * c[2];
	matrix[2][0] = v[0] * tmp[2] + v[1] * c[2];
	matrix[0][1] = v[1] * tmp[0] + v[2] * c[2];
	matrix[1][1] = c[0] + v[1] * tmp[1];
	matrix[2][1] = v[1] * tmp[2] - v[0] * c[2];
	matrix[0][2] = v[2] * tmp[0] - v[1] * c[2];
	matrix[1][2] = v[2] * tmp[1] + v[0] * c[2];
	matrix[2][2] = c[0] + v[2] * tmp[2];
}

t_vec			matrix_mul_vec(t_vec matrix[3], t_vec v)
{
	return ((matrix[0] + matrix[1] + matrix[2]) * v);
}
