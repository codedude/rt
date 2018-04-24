/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:38:03 by vparis            #+#    #+#             */
/*   Updated: 2018/04/24 14:16:53 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		solve_quadra(t_float abc[3])
{
	t_float	r;
	t_float	s[2];

	r = abc[1] * abc[1] - (4. * abc[0] * abc[2]);
	if (r < 0.)
		return (FLOAT_ZERO);
	if (r == 0.)
		s[0] = -abc[1] / (2. * abc[0]);
	else
	{
		r = sqrt(r);
		s[0] = (-abc[1] + r) / (2. * abc[0]);
		s[1] = (-abc[1] - r) / (2. * abc[0]);
	}
	if (s[0] < FLOAT_MIN && s[1] < FLOAT_MIN)
		return (FLOAT_ZERO);
	if (s[0] < FLOAT_MIN)
		s[0] = s[1];
	else if (s[1] > FLOAT_MIN && s[1] < s[0])
		s[0] = s[1];
	return (s[0]);
}
