/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 11:01:42 by hcaillau          #+#    #+#             */
/*   Updated: 2018/03/08 13:55:12 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib_vec.h"

VEC3		point_ray_intersect(double t, RAY ray)
{
	VEC3	coord;

	coord = scaling(ray.direction, t);
	coord = vec_add(coord, ray.origin);
	return (coord);
}

VEC3		sphere_normal(VEC3 center, VEC3 point)
{
	VEC3	ret;

	ret = from_to(center, point);
	ret = vec3_normalize(ret);
	return (ret);
}

VEC3		cyl_normal(VEC3 bottom, VEC3 top, VEC3 point)
{
	VEC3	ret;
	VEC3	axis;
	VEC3	pt_dir;
	VEC3	bot_dir;

	bot_dir = from_to(point, bottom);
	axis = vec3_normalize(from_to(bottom, top));
	pt_dir = from_to(bottom, point);
	pt_dir = mat3_mult_vec3(rot_around_vec(axis, M_PI), pt_dir);
	pt_dir = vec_add(bottom, pt_dir);
	ret = vec3_normalize(from_to(pt_dir, point));
	return (ret);
}

VEC3		cone_normal(t_cone c, VEC3 point)
{
	VEC3	ret;
	VEC3	v;
	VEC3	ap;

	v = vec3_normalize(from_to(c.bottom, c.apex));
	ap = from_to(c.apex, point);
	ret = scaling(v, ((1 + pow(tan(c.angle), 2)) * dot(vec3_opposite(ap), v)));
	ret = vec_add(ap, ret);
	ret = vec3_normalize(ret);
	return (ret);
}
