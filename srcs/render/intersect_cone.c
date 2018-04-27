/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:45:05 by mcasubol          #+#    #+#             */
/*   Updated: 2018/04/27 10:24:44 by valentin         ###   ########.fr       */
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
	vec[0] -= vec[2];
	abc[0] = cos2sin2[0] * vec_dot(vec[3], vec[3])
			- cos2sin2[1] * dvpva[0] * dvpva[0];
	abc[1] = 2.0 * cos2sin2[0] * vec_dot(vec[3], vec[0])
			- 2.0 * cos2sin2[1] * dvpva[0] * dvpva[1];
	abc[2] = cos2sin2[0] * vec_dot(vec[0], vec[0])
			- cos2sin2[1] * dvpva[1] * dvpva[1];
	return ((*t = solve_quadra(abc)));
}
/*
	t_vec3	vec[4];
	t_f64	abc[3];
	t_f64	cos2sin2[2];
	t_f64	dvpva[2];

	cos2sin2[0] = (1. + ft_cos(2. * obj->radius)) / 2.;
	cos2sin2[1] = (1. - ft_cos(2. * obj->radius)) / 2.;
	vec3_cpy(&vec[0], &(ray->orig));
	vec3_sub(&vec[0], &(obj->pos));
	dvpva[0] = vec3_dot(&(ray->dir), &(obj->norm));
	vec3_cpy(&vec[1], &(obj->norm));
	vec3_mul_scalar(&vec[1], dvpva[0]);
	vec3_cpy(&vec[2], &(obj->norm));
	dvpva[1] = vec3_dot(&vec[0], &(obj->norm));
	vec3_mul_scalar(&vec[2], dvpva[1]);
	vec3_cpy(&vec[3], &(ray->dir));
	vec3_sub(&vec[3], &vec[1]);
	abc[0] = cos2sin2[0] * vec3_dot(&vec[3], &vec[3])
			- cos2sin2[1] * dvpva[0] * dvpva[0];
	vec3_sub(&vec[0], &vec[2]);
	abc[1] = 2. * cos2sin2[0] * vec3_dot(&vec[3], &vec[0])
			- 2. * cos2sin2[1] * dvpva[0] * dvpva[1];
	abc[2] = cos2sin2[0] * vec3_dot(&vec[0], &vec[0])
			- cos2sin2[1] * dvpva[1] * dvpva[1];
	return (solve_quadra(abc, solution));
*/
void		norm_cone(t_ray *ray, t_object *obj, t_inter *inter)
{
	t_float	t;
	t_vec	tmp;

	(void)ray;
	tmp = inter->point - obj->pos;
	t = ft_cos(2.0 * obj->radius);
	t = (1.0 + (1.0 - t) / (1.0 + t)) * vec_dot(tmp, obj->dir);
	inter->normal = vec_norm((obj->dir * -t) + tmp);
}
/*
	t_f64	t;
	t_vec3	tmp;

	vec3_cpy(&(ray_hit->dir), &(ray_hit->orig));
	vec3_sub(&(ray_hit->dir), &(obj->pos));
	t = ft_cos(2.0 * obj->radius);
	t = 1.0 + (1.0 - t) / (1.0 + t);
	t *= vec3_dot(&(ray_hit->dir), &(obj->norm));
	vec3_cpy(&tmp, &(ray_hit->orig));
	vec3_sub(&tmp, &(obj->pos));
	vec3_cpy(&(ray_hit->dir), &(obj->norm));
	vec3_mul_scalar(&(ray_hit->dir), -t);
	vec3_add(&(ray_hit->dir), &tmp);
	vec3_norm(&(ray_hit->dir));
*/