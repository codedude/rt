/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 18:51:24 by vparis            #+#    #+#             */
/*   Updated: 2018/04/26 19:37:12 by vparis           ###   ########.fr       */
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
	t_vec	delta_p;
	t_vec	vva;
	t_vec	dpva;
	t_vec	tmp;
	t_float	abc[3];

	delta_p = ray->origin - obj->pos;
	vva = obj->dir * vec_dot(ray->dir, obj->dir);
	dpva = obj->dir * vec_dot(delta_p, obj->dir);
	delta_p -= dpva;
	tmp = ray->dir - vva;
	abc[0] = vec_dot(tmp, tmp);
	abc[1] = 2.0 * vec_dot(tmp, delta_p);
	abc[2] = vec_dot(delta_p, delta_p) - obj->radius2;
	return ((*t = solve_quadra(abc)));
}

void		norm_cylinder(t_ray *ray, t_object *obj, t_inter *inter)
{
	t_vec		matrix[3];

	(void)ray;
	matrix_rot_vec(matrix, obj->dir, 180.0);
	inter->normal = vec_norm(inter->normal
		- (matrix_mul_vec(matrix, inter->point - obj->pos) + obj->pos));
}
