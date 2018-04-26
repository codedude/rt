/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:32:55 by vparis            #+#    #+#             */
/*   Updated: 2018/04/26 14:42:03 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_plane(t_ray *ray, t_object *obj, t_float *t)
{
	t_float	denom;
	t_vec	diff;

	denom = vec_dot(obj->dir, ray->dir);
	if (denom > FLOAT_MIN || denom < -FLOAT_MIN)
	{
		diff = obj->pos - ray->origin;
		*t = vec_dot(diff, obj->dir) / denom;
		return (SUCCESS);
	}
	return (ERROR);
}

void		norm_plane(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	inter->normal = obj->dir;
}
