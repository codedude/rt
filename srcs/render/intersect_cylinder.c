/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 18:51:24 by vparis            #+#    #+#             */
/*   Updated: 2018/04/27 15:26:31 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_cylinder(t_ray *ray, t_object *obj, t_float *t)
{
	t_float	abc[3];

	abc[0] = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	abc[1] = 2.0 * ray->dir.x * ray->origin.x + 2.0 * ray->dir.z * ray->origin.z;
	abc[2] = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - obj->radius * obj->radius;
	return ((*t = solve_quadra(abc)));
}

void		norm_cylinder(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	if (inter->obj_coord.x > -1.0 && inter->obj_coord.x < 1.0)
		vec_print(inter->obj_coord, "coord en 00");
	inter->normal = vec_norm(VEC_INIT(inter->obj_coord.x, 0.0, inter->obj_coord.z));
}
