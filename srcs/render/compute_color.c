/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:44:24 by vparis            #+#    #+#             */
/*   Updated: 2018/04/26 17:09:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "types.h"
#include "objects.h"
#include "sdl_m.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

void		init_ray_light(t_ray *ray_light, t_float *max_dist, t_object *obj,
							t_inter *inter)
{
	if (obj->type == LIGHT_POINT)
	{
		ray_light->dir = obj->pos - inter->point;
		*max_dist = 1.0;
	}
	else if (obj->type == LIGHT_PAR)
	{
		ray_light->dir = vec_norm(obj->dir * -1.0);
		*max_dist = FLOAT_MAX;
	}
	ray_light->origin = inter->point_biais;
}

t_vec		diffuse(t_rt *rt, t_object *obj, t_inter *inter, t_hit *light_hit)
{
	t_float		max_dist;
	t_vec		intensity;
	t_ray		ray_refract;
	t_inter		inter_refract;

	init_ray_light(&light_hit->ray, &max_dist, obj, inter);
	if (trace(rt, &light_hit->ray, &light_hit->inter, max_dist) == SUCCESS)
	{
		intensity = VEC_ZERO;
		/*if (light_hit->inter.obj->refraction >= 1.0
			&& light_hit->inter.obj->transparency > 0.0)
		{
			refract_ray(&light_hit->ray, inter);
			if (trace(rt, &ray_refract, &inter_refract, FLOAT_MAX) == ERROR)
			{
				intensity += obj->intensity
					* light_hit->inter.obj->transparency);
			}
		}*/
	}
	else
	{
		intensity = obj->intensity;
	}
	if (obj->type == LIGHT_POINT)
		light_hit->ray.dir = vec_norm(light_hit->ray.dir);
	return (intensity);
}

t_vec		local(t_rt *rt, t_object *obj, t_hit *hit)
{
	t_hit	light_hit;
	t_vec	intensity_local;
	t_vec	intensity;
	t_float	dot;
	t_vec	reflect_ray;

	intensity = VEC_ZERO;
	intensity_local = diffuse(rt, obj, &hit->inter, &light_hit);
	if (intensity_local[0] > 0.0 || intensity_local[1] > 0.0
		|| intensity_local[2] > 0.0)
	{
		dot = vec_dot(light_hit.ray.dir, hit->inter.normal);
		if (dot > FLOAT_ZERO)
		{
			intensity = intensity_local
				* (dot * hit->inter.obj->phong[PHONG_KD]);
			if (hit->inter.obj->phong[PHONG_SHINI] > 0.0)
			{
				reflect_ray = vec_norm((hit->inter.normal * (-2.0 * dot))
					+ light_hit.ray.dir);
				dot = vec_dot(reflect_ray, hit->ray.dir);
				if (dot > FLOAT_ZERO)
				{
					intensity += intensity_local
						* (pow(dot, hit->inter.obj->phong[PHONG_SHINI])
						* hit->inter.obj->phong[PHONG_KS]);
				}
			}
		}
	}
	return (intensity);
}

t_vec		compute_local_light(t_rt *rt, t_hit *hit)
{
	int			i;
	t_vec		intensity;
	t_object	*objs;

	intensity = VEC_ZERO;
	i = 0;
	objs = rt->objects.objects_array;
	while (i < rt->objects.size)
	{
		if (object_is_light(&objs[i]))
		{
			if (objs[i].type == LIGHT_AMBIENT)
				intensity += objs[i].intensity;
			else
			{
				intensity += local(rt, &objs[i], hit);
			}
		}
		i++;
	}
	return (intensity);
}

t_color		compute_color(t_rt *rt, t_hit *hit, int depth)
{
	t_vec		intensity;
	t_color		color;

	if (trace(rt, &hit->ray, &hit->inter, FLOAT_MAX) == SUCCESS)
	{
		hit->inter.point = (hit->ray.dir * hit->inter.t)
			+ hit->ray.origin;
		compute_hit_normal(&hit->ray, &hit->inter);
		compute_hit_biais(&hit->inter);
		if (vec_dot(hit->ray.dir, hit->inter.normal) > FLOAT_ZERO)
			hit->inter.normal *= -1.0;
		intensity = compute_local_light(rt, hit);
		color = vec_to_color(intensity * hit->inter.obj->color);
	}
	else
		color = rt->canvas.bg_color;

	return (color);
}
