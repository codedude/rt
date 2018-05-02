/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:56:40 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/02 19:48:43 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"
#include "stdio.h"

int			is_cut(t_object *obj, t_hit *hit, t_float t, t_ray *simple)
{
	t_vec	inter;
	t_vec	low;
	t_vec	up;

	if (obj->is_limited != 1 && obj->is_limited != 2)
		return (0);
	if (obj->is_limited == 1)
		inter = simple->origin + simple->dir * t;
	else
		inter = hit->ray.origin + hit->ray.dir * t;
	low = obj->lower_limit;
	up = obj->upper_limit;
	if (inter.x > low.x && inter.x < up.x
		&& inter.y > low.y && inter.y < up.y
		&& inter.z > low.z && inter.z < up.z)
		return (0);
	return (1);
}
