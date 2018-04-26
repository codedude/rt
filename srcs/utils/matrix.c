/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/26 19:34:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "ft_math.h"
#include "vec.h"


void		matrix_rot_vec(t_vec matrix[3], t_vec v, t_float ang)
{
	t_float	c;
	t_float	c1;
	t_float	s;

	c = ft_cos(ang);
	c1 = 1. - c;
	s = ft_sin(ang);
	matrix[0][0] = c + v[0] * v[0] * c1;
	matrix[1][0] = v[0] * v[1] * c1 - v[2] * s;
	matrix[2][0] = v[0] * v[2] * c1 + v[1] * s;

	matrix[0][1] = v[1] * v[0] * c1 + v[2] * s;
	matrix[1][1] = c + v[1] * v[1] * c1;
	matrix[2][1] = v[1] * v[2] * c1 - v[0] * s;
	
	matrix[0][2] = v[2] * v[0] * c1 - v[1] * s;
	matrix[1][2] = v[2] * v[1] * c1 + v[0] * s;
	matrix[2][2] = c + v[2] * v[2] * c1;
}

t_vec		matrix_mul_vec(t_vec matrix[3], t_vec v)
{
	return ((matrix[0] + matrix[1] + matrix[2]) * v);
}
