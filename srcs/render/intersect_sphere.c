/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:33:02 by vparis            #+#    #+#             */
/*   Updated: 2018/04/26 16:41:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_sphere(t_ray *ray, t_object *obj, t_float *t)
{
	t_float	abc[3];
	t_vec	d;
	t_vec	co;

	d = ray->dir;
	co = ray->origin;
	abc[0] = vec_dot(d, d);
	abc[1] = 2.0 * vec_dot(co, d);
	abc[2] = vec_dot(co, co) - obj->radius * obj->radius;
	return ((*t = solve_quadra(abc)));
}

void		norm_sphere(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	inter->normal = vec_norm(inter->point - obj->pos);
}
