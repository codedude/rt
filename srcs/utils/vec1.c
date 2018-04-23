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