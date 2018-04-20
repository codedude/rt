/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:31:45 by hcaillau          #+#    #+#             */
/*   Updated: 2018/02/22 15:56:34 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib_vec.h"

VEC2	new_vec2(double x, double y)
{
	VEC2 v;

	v.x = x;
	v.y = y;
	return (v);
}

VEC2	vec2_add(VEC2 a, VEC2 b)
{
	VEC2 ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}

VEC2	vec2_opposite(VEC2 a)
{
	a.x *= -1;
	a.y *= -1;
	return (a);
}

VEC2	vec2_from_to(VEC2 from, VEC2 to)
{
	VEC2 ret;

	ret.x = to.x - from.x;
	ret.y = to.y - from.y;
	return (ret);
}

VEC2	vec2_scaling(VEC2 vec, double a)
{
	vec.x *= a;
	vec.y *= a;
	return (vec);
}
