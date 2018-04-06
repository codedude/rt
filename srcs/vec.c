/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:56:56 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 17:38:37 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "types.h"

t_float		vec_dot(t_vec v1, t_vec v2)
{
	return (v1.s[0] * v2.s[0] + v1.s[1] * v2.s[1] + v1.s[2] * v2.s[2]);
}

t_float		vec_len(t_vec v1)
{
	return (sqrt(vec_dot(v1, v1)));
}

void			vec_norm(t_vec v1)
{
	t_float	len;

	len = vec_len(v1);
	if (len > 0.0)
	{
		len = 1.0 / sqrt(len);
		v1.s[0] *= len;
		v1.s[1] *= len;
		v1.s[2] *= len;
	}
}
