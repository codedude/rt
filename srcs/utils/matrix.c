/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/27 22:06:21 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "ft_math.h"
#include <math.h>
#include <stdio.h>
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

void			matrix_mul_matrix(t_vec m1[3], t_vec m2[3], t_vec ret[3])
{
	ret[0] = VEC_INIT(
		m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
		m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
		m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2]
						);
	ret[1] = VEC_INIT(
		m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
		m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
		m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2]
						);
	ret[2] = VEC_INIT(
		m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
		m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
		m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2]
						);
}

void	matrix_rotx(t_vec ret[3], double teta)
{
	double	angle;

	angle = DEG_TO_RAD * teta;
	ret[0] = VEC_INIT(1.0, 0.0, 0.0);
	ret[1] = VEC_INIT(0.0, cos(angle), sin(angle));
	ret[2] = VEC_INIT(0.0, -sin(angle), cos(angle));
}

void	matrix_roty(t_vec ret[3], double teta)
{
	double	angle;

	angle = DEG_TO_RAD * teta;
	ret[0] = VEC_INIT(cos(angle), 0.0, -sin(angle));
	ret[1] = VEC_INIT(0.0, 1.0, 0.0);
	ret[2] = VEC_INIT(sin(angle), 0.0, cos(angle));
}

void	matrix_rotz(t_vec ret[3], double teta)
{
	double	angle;

	angle = DEG_TO_RAD * teta;
	ret[0] = VEC_INIT(cos(angle), sin(angle), 0.0);
	ret[1] = VEC_INIT(-sin(angle), cos(angle), 0.0);
	ret[2] = VEC_INIT(0.0, 0.0, 1.0);
}

void	matrix_equal_matrix(t_vec m1[3], t_vec m2[3])
{
	m1[0] = VEC_INIT(m2[0][0], m2[0][1], m2[0][2]);
	m1[1] = VEC_INIT(m2[1][0], m2[1][1], m2[1][2]);
	m1[2] = VEC_INIT(m2[2][0], m2[2][1], m2[2][2]);
}

void	matrix_id(t_vec m[3])
{
	m[0] = VEC_INIT(1.0, 0.0, 0.0);
	m[1] = VEC_INIT(0.0, 1.0, 0.0);
	m[2] = VEC_INIT(0.0, 0.0, 1.0);
}

void	inverse_matrix(t_vec m[3], t_vec inv[3])
{
	t_float	det;
	t_vec	comat[3];
	t_vec	transpo[3];

	det = matrix_det(m);
	comatrix(m, comat);
	transpose_matrix(comat, transpo);
	inv[0] = (1.0 / det) * transpo[0];
	inv[1] = (1.0 / det) * transpo[1];
	inv[2] = (1.0 / det) * transpo[2];
}
void	transpose_matrix(t_vec m[3], t_vec tr[3])
{
	tr[0] = VEC_INIT(m[0][0], m[1][0], m[2][0]);
	tr[1] = VEC_INIT(m[0][1], m[1][1], m[2][1]);
	tr[2] = VEC_INIT(m[0][2], m[1][2], m[2][2]);
}

void	comatrix(t_vec m[3], t_vec ret[3])
{
	ret[0] = VEC_INIT(m[1][1] * m[2][2] - m[2][1] * m[1][2],
					m[1][2] * m[2][0] - m[1][0] * m[2][2],
					m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	ret[1] = VEC_INIT(m[2][1] * m[0][2] - m[0][1] * m[2][2],
					m[0][0] * m[2][2] - m[0][2] * m[2][0],
					m[0][1] * m[2][0] - m[0][0] * m[2][1]);
	ret[2] = VEC_INIT(m[0][1] * m[1][2] - m[1][1] * m[0][2],
					m[0][2] * m[1][0] - m[0][0] * m[1][2],
					m[0][0] * m[1][1] - m[0][1] * m[1][0]);
}

t_float	matrix_det(t_vec m[3])
{
	t_float	det;

	det = (m[0][0] * m[1][1] * m[2][2])
		+ (m[1][0] * m[2][1] * m[0][2])
		+ (m[2][0] * m[0][1] * m[1][2])
		- (m[0][2] * m[1][1] * m[2][0])
		- (m[1][2] * m[2][1] * m[0][0])
		- (m[2][2] * m[0][1] * m[1][0]);
	return (det);
}

void	print_matrix(t_vec m[3], char *str)
{
	printf("%s\n", str);
	vec_print(m[0], "m0");
	vec_print(m[1], "m1");
	vec_print(m[2], "m2");
	printf("\n");
}
