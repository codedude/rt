/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/27 15:33:42 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "ft_math.h"
#include "vec.h"

static t_float	g_c[3];

void			matrix_init_value(void)
{
	g_c[0] = ft_cos(180.0);
	g_c[1] = 1.0 - g_c[0];
	g_c[2] = ft_sin(180.0);
}

void			matrix_rot_vec(t_vec matrix[3], t_vec v)
{
	t_vec	tmp_c;
	t_vec	tmp_s;

	tmp_c = v * g_c[1];
	tmp_s = v * g_c[2];
	matrix[0] = VEC_INIT(
			g_c[0] + v[0] * tmp_c[0],
			v[1] * tmp_c[0] + tmp_s[2],
			v[2] * tmp_c[0] - tmp_s[1]);
	matrix[1] = VEC_INIT(
			v[0] * tmp_c[1] - tmp_s[2],
			g_c[0] + v[1] * tmp_c[1],
			v[2] * tmp_c[1] + tmp_s[0]);
	matrix[2] = VEC_INIT(
			v[0] * tmp_c[2] + tmp_s[1],
			v[1] * tmp_c[2] - tmp_s[0],
			g_c[0] + v[2] * tmp_c[2]);
}

t_vec			matrix_mul_vec(t_vec matrix[3], t_vec v)
{
	return (matrix[0] * v[0] + matrix[1] * v[1] + matrix[2] * v[2]);
}
