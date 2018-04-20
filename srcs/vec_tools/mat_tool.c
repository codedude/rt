/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:31:35 by hcaillau          #+#    #+#             */
/*   Updated: 2018/02/22 17:06:02 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rtv1.h"
#include "../includes/lib_vec.h"

VEC3	transformation(VEC3 v, MAT3 m, VEC3 t)
{
	v = mat3_mult_vec3(m, v);
	v = translation(v, t);
	return (v);
}

MAT3	mat3_identity(void)
{
	return ((MAT3){ .m = {
				1, 0, 0,
				0, 1, 0,
				0, 0, 1
				}});
}

VEC3	mat3_mult_vec3(MAT3 m, VEC3 v)
{
	VEC3	tmp;

	tmp = v;
	tmp.x = v.x * m.m[0] + v.y * m.m[1] + v.z * m.m[2];
	tmp.y = v.x * m.m[3] + v.y * m.m[4] + v.z * m.m[5];
	tmp.z = v.x * m.m[6] + v.y * m.m[7] + v.z * m.m[8];
	return (tmp);
}

MAT3	mat3_mult_mat3(MAT3 m, MAT3 t)
{
	MAT3	ret;

	ret = (MAT3){ .m = {
		m.m[0] * t.m[0] + m.m[1] * t.m[3] + m.m[2] * t.m[6],
		m.m[0] * t.m[1] + m.m[1] * t.m[4] + m.m[2] * t.m[7],
		m.m[0] * t.m[2] + m.m[1] * t.m[5] + m.m[2] * t.m[8],
		m.m[3] * t.m[0] + m.m[4] * t.m[3] + m.m[5] * t.m[6],
		m.m[3] * t.m[1] + m.m[4] * t.m[4] + m.m[5] * t.m[7],
		m.m[3] * t.m[2] + m.m[4] * t.m[5] + m.m[5] * t.m[8],
		m.m[6] * t.m[0] + m.m[7] * t.m[3] + m.m[8] * t.m[6],
		m.m[6] * t.m[1] + m.m[7] * t.m[4] + m.m[8] * t.m[7],
		m.m[6] * t.m[2] + m.m[7] * t.m[5] + m.m[8] * t.m[8]
				}};
	return (ret);
}

void	mat3_print(MAT3 m)
{
	printf("(%f, %f, %f)\n", m.m[0], m.m[1], m.m[2]);
	printf("(%f, %f, %f)\n", m.m[3], m.m[4], m.m[5]);
	printf("(%f, %f, %f)\n", m.m[6], m.m[7], m.m[8]);
	printf("\n");
}
