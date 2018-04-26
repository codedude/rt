/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:45:05 by mcasubol          #+#    #+#             */
/*   Updated: 2018/04/26 19:39:11 by vparis           ###   ########.fr       */
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
	t_vec	vec[4];
	t_float	abc[3];
	t_float	cos2sin2[2];
	t_float	dvpva[2];

	cos2sin2[0] = (1. + ft_cos(2. * obj->radius)) / 2.;
	cos2sin2[1] = (1. - ft_cos(2. * obj->radius)) / 2.;
	vec[0] = ray->origin - obj->pos;
	dvpva[0] = vec_dot(ray->dir, obj->dir);
	vec[1] = obj->dir * dvpva[0];
	dvpva[1] = vec_dot(vec[0], obj->dir);
	vec[2] = obj->dir * dvpva[1];
	vec[3] = ray->dir - vec[1];
	abc[0] = cos2sin2[0] * vec_dot(vec[3], vec[3])
			- cos2sin2[1] * dvpva[0] * dvpva[0];
	vec[0] -= vec[2];
	abc[1] = 2. * cos2sin2[0] * vec_dot(vec[3], vec[0])
			- 2. * cos2sin2[1] * dvpva[0] * dvpva[1];
	abc[2] = cos2sin2[0] * vec_dot(vec[0], vec[0])
			- cos2sin2[1] * dvpva[1] * dvpva[1];
	return ((*t = solve_quadra(abc)));
}

void		norm_cone(t_ray *ray, t_object *obj, t_inter *inter)
{
	t_float	t;
	t_vec	tmp;

	(void)ray;
	tmp = inter->point - obj->pos;
	t = ft_cos(2.0 * obj->radius);
	t = (1.0 + (1.0 - t) / (1.0 + t)) * vec_dot(tmp, obj->dir);
	inter->normal = (obj->dir * -t) + tmp;
	inter->normal = vec_norm(inter->normal);
}
