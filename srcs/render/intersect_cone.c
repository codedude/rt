/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:45:05 by mcasubol          #+#    #+#             */
/*   Updated: 2018/04/27 15:26:43 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "ft_math.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_cone(t_ray *ray, t_object *obj, t_float *t)
{
	t_float	abc[3];
	
	abc[0] = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z - obj->radius * ray->dir.y * ray->dir.y;
	abc[1] = 2.0 * (ray->dir.x * ray->origin.x + ray->dir.z * ray->origin.z - obj->radius * ray->dir.y * ray->origin.y);
	abc[2] = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - obj->radius * ray->origin.y * ray->origin.y;
	return ((*t = solve_quadra(abc)));
}

void		norm_cone(t_ray *ray, t_object *obj, t_inter *inter)
{
	t_float	t;
	t_vec	tmp;

	if (inter->obj_coord.x > -1.0 && inter->obj_coord.x < 1.0 && inter->obj_coord.z > -1.0 && inter->obj_coord.z < 1.0)
		vec_print(inter->obj_coord, "coord en 00");
	(void)ray;
	tmp = inter->point - obj->pos;
	t = ft_cos(2.0 * obj->radius);
	t = (1.0 + (1.0 - t) / (1.0 + t)) * vec_dot(tmp, obj->dir);
	inter->normal = vec_norm((obj->dir * -t) + tmp);
}
