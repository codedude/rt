/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:56:56 by vparis            #+#    #+#             */
/*   Updated: 2018/04/20 16:01:41 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "types.h"

t_float		vec_dot(t_vec v1, t_vec v2)
{
	t_vec	r;

	r = v1 * v2;
	return (r[0] + r[1] + r[2]);
}

t_float		vec_len(t_vec v1)
{
	return (sqrt(vec_dot(v1, v1)));
}

void		vec_norm(t_vec v1)
{
	t_float	len;

	len = vec_len(v1);
	if (len > 0.0)
	{
		len = 1.0 / len;
		v1[0] *= len;
		v1[1] *= len;
		v1[2] *= len;
	}
}

t_vec		vec3_add(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec		from_to(t_vec from, t_vec to)
{
	t_vec	ret;

	ret.x = to.x - from.x;
	ret.y = to.y - from.y;
	ret.z = to.z - from.z;
	return (ret);
}