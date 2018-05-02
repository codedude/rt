/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:56:40 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/02 22:11:51 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

static int	in_limit(t_float t, t_vec inter, t_object *obj)
{
	t_vec	low;
	t_vec	up;

	low = obj->lower_limit;
	up = obj->upper_limit;
	if (inter.x > low.x && inter.x < up.x
		&& inter.y > low.y && inter.y < up.y
		&& inter.z > low.z && inter.z < up.z)
		return (1);
	return (0);
}

int			is_cut(t_object *obj, t_hit *hit, t_float *t, t_ray *simple)
{
	t_vec	inter[2];
	int		i;

	i = -1;
	while (++i < 2)
	{
		if (obj->is_limited == 1)
			inter[i] = simple->origin + simple->dir * hit->inter.t2[i];
		else
			inter[i] = hit->ray.origin + hit->ray.dir * hit->inter.t2[i];
	}
	if (in_limit(hit->inter.t2[0], inter[0], obj))
	{
		if (in_limit(hit->inter.t2[1], inter[1], obj))
		{
			*t = (hit->inter.t2[0] < hit->inter.t2[1]) ? hit->inter.t2[0] : hit->inter.t2[1];
			return (0);
		}
		*t = hit->inter.t2[0];
		return (0);
	}
	if (in_limit(hit->inter.t2[1], inter[1], obj))
	{
		*t = hit->inter.t2[1];
		return (0);
	}
	return (1);
}
