/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcasubol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:56:40 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/01 17:55:10 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"
#include "stdio.h"

int			is_cut(t_object obj, t_hit *hit, t_float t, t_ray simple)
{
	t_vec	inter;
	t_vec	low;
	t_vec	up;

	if (obj.is_limited != 1 && obj.is_limited != 2)
		return (0);
	hit->inter.point = hit->ray.origin + hit->ray.dir * t;
	hit->inter.obj_coord = simple.origin + simple.dir * t;
	inter = (obj.is_limited == 1) ? hit->inter.obj_coord : hit->inter.point;
	low = obj.lower_limit;
	up = obj.upper_limit;
	//printf("%f, %f, %f, %f, %f, %f\n", low.x, low.y, low.z, up.x, up.y, up.z);
	//printf("%f, %f, %f\n", inter.x, inter.y, inter.z);
	if (inter.x > low.x && inter.x < up.x
		&& inter.y > low.y && inter.y < up.y
		&& inter.z > low.z && inter.z < up.z)
		return (0);
	return (1);
}
