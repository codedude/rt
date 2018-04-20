/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 10:46:32 by hcaillau          #+#    #+#             */
/*   Updated: 2018/02/22 15:23:25 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib_vec.h"
#include "../../../includes/rtv1.h"

MAT3	mat3_rotx(double teta)
{
	MAT3	ret;
	double	angle;

	angle = ft_torad(teta);
	ret = (MAT3){ .m = {
		1, 0, 0,
		0, cos(angle), -sin(angle),
		0, sin(angle), cos(angle)
	}};
	return (ret);
}

MAT3	mat3_roty(double teta)
{
	MAT3	ret;
	double	angle;

	angle = ft_torad(teta);
	ret = (MAT3){ .m = {
		cos(angle), 0, sin(angle),
		0, 1, 0,
		-sin(angle), 0, cos(angle)
	}};
	return (ret);
}

MAT3	mat3_rotz(double teta)
{
	MAT3	ret;
	double	angle;

	angle = ft_torad(teta);
	ret = (MAT3){ .m = {
		cos(angle), -sin(angle), 0,
		sin(angle), cos(angle), 0,
		0, 0, 1
	}};
	return (ret);
}

MAT3	rot_around_vec(VEC3 d, double teta)
{
	MAT3	ret;
	double	c;
	double	s;

	c = cos(teta);
	s = sin(teta);
	ret = (MAT3){ .m = {
		d.x * d.x * (1 - c) + c,
		d.x * d.y * (1 - c) - d.z * s,
		d.x * d.z * (1 - c) + d.y * s,
		d.x * d.y * (1 - c) + d.z * s,
		d.y * d.y * (1 - c) + c,
		d.y * d.z * (1 - c) - d.x * s,
		d.x * d.z * (1 - c) - d.y * s,
		d.y * d.z * (1 - c) + d.x * s,
		d.z * d.z * (1 - c) + c,
	}};
	return (ret);
}
