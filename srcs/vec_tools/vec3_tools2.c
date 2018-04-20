/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:17:44 by hcaillau          #+#    #+#             */
/*   Updated: 2018/03/08 18:01:04 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

double		dot(VEC3 a, VEC3 b)
{
	double	ret;

	ret = a.x * b.x + a.y * b.y + a.z * b.z;
	return (ret);
}

VEC3		new_vec3(double x, double y, double z)
{
	VEC3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

VEC3		vec_add(VEC3 a, VEC3 b)
{
	VEC3	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

VEC3		vec3_sub(VEC3 a, VEC3 b)
{
	VEC3	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

VEC3		vec3_opposite(VEC3 a)
{
	a.x *= -1.0;
	a.y *= -1.0;
	a.z *= -1.0;
	return (a);
}
