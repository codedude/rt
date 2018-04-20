/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:31:46 by hcaillau          #+#    #+#             */
/*   Updated: 2018/03/08 14:26:10 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

VEC3		from_to(VEC3 from, VEC3 to)
{
	VEC3	ret;

	ret.x = to.x - from.x;
	ret.y = to.y - from.y;
	ret.z = to.z - from.z;
	return (ret);
}

VEC3		scaling(VEC3 vec, double a)
{
	VEC3	ret;

	ret.x = vec.x * a;
	ret.y = vec.y * a;
	ret.z = vec.z * a;
	return (ret);
}

VEC3		translation(VEC3 vec, VEC3 trans)
{
	vec.x += trans.x;
	vec.y += trans.y;
	vec.z += trans.z;
	return (vec);
}

double		vec3_length(VEC3 v)
{
	double	ret;

	ret = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (ret);
}

VEC3		vec3_normalize(VEC3 v)
{
	double	length;

	if ((length = 1.0 / vec3_length(v)))
	{
		v.x *= length;
		v.y *= length;
		v.z *= length;
	}
	return (v);
}

void		print_vec3(VEC3 v)
{
	printf("(%f ||  %f || %f)\n", v.x, v.y, v.z);
}
