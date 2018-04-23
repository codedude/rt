/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:38:03 by vparis            #+#    #+#             */
/*   Updated: 2018/04/23 22:59:22 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		solve_quadra(t_float abc[3], t_float *t)
{
	t_float	r;
	t_float	s[2];

	r = abc[1] * abc[1] - (4. * abc[0] * abc[2]);
	if (r < 0.)
		return (ERROR);
	if (r == 0.)
		s[0] = -abc[1] / (2. * abc[0]);
	else
	{
		r = sqrt(r);
		s[0] = (-abc[1] + r) / (2. * abc[0]);
		s[1] = (-abc[1] - r) / (2. * abc[0]);
	}
	if (s[0] < FLOAT_MIN && s[1] < FLOAT_MIN)
		return (ERROR);
	if (s[0] < FLOAT_MIN)
		s[0] = s[1];
	else if (s[1] > FLOAT_MIN && s[1] < s[0])
		s[0] = s[1];
	*t = s[0];
	return (SUCCESS);
}
