/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:33:02 by vparis            #+#    #+#             */
/*   Updated: 2018/04/23 17:52:41 by vparis           ###   ########.fr       */
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
	co = ray->origin - obj->pos;
	abc[0] = vec_dot(d, d);
	abc[1] = 2.0 * vec_dot(co, d);
	abc[2] = vec_dot(co, co) - obj->radius2;
	return (solve_quadra(abc, t));
}

void		norm_sphere(t_ray *ray, t_object *obj, t_inter *inter)
{
	inter->normal = ray->origin - obj->pos;
	vec_norm(inter->normal);
}
