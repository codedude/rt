/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:44:24 by vparis            #+#    #+#             */
/*   Updated: 2018/04/24 19:47:12 by vparis           ###   ########.fr       */
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
		ray_light->dir = vec_scalar(obj->dir, -1.0);
		ray_light->dir = vec_norm(ray_light->dir);
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

	intensity = (t_vec){0.0, 0.0, 0.0, 0.0};
	init_ray_light(&light_hit->ray, &max_dist, obj, inter);
	if (trace(rt, &light_hit->ray, &light_hit->inter, max_dist) == SUCCESS)
	{
		/*if (light_hit->inter.obj->refraction >= 1.0
			&& light_hit->inter.obj->transparency > 0.0)
		{
			refract_ray(&light_hit->ray, inter);
			if (trace(rt, &ray_refract, &inter_refract, FLOAT_MAX) == ERROR)
			{
				intensity += vec_scalar(obj->intensity,
					light_hit->inter.obj->transparency);
			}
		}*/
	}
	else
	{
		intensity += obj->intensity;
	}
	if (obj->type == LIGHT_POINT)
		light_hit->ray.dir = vec_norm(light_hit->ray.dir);
	return (intensity);
}

t_vec		local(t_rt *rt, t_object *obj, t_hit *hit)
{
	t_hit	light_hit;
	t_vec	intensity;
	t_float	dot;


	intensity = diffuse(rt, obj, &hit->inter, &light_hit);
	if (intensity[0] != 0.0)
	{
		dot = vec_dot(hit->inter.normal, light_hit.ray.dir);
		if (dot < FLOAT_MIN)
			intensity = (t_vec){0.0, 0.0, 0.0, 0.0};
		else if (hit->inter.obj->phong[PHONG_SHINI] > 0.0)
		{
			intensity = vec_scalar(intensity,
				dot * hit->inter.obj->phong[PHONG_KD]);
			intensity += vec_scalar(intensity,
				pow(dot, hit->inter.obj->phong[PHONG_SHINI])
				* hit->inter.obj->phong[PHONG_KS]);
		}
	}
	return (intensity);
}

t_vec		compute_local_light(t_rt *rt, t_hit *hit)
{
	int			i;
	t_vec		intensity;
	t_object	*objs;

	intensity = (t_vec){0.0, 0.0, 0.0, 0.0};
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
		compute_hit_normal(&hit->ray, &hit->inter);
		hit->inter.point = vec_scalar(hit->ray.dir, hit->inter.t)
			+ hit->ray.origin;
		compute_hit_biais(&hit->inter);
		if (vec_dot(hit->ray.dir, hit->inter.normal) > FLOAT_ZERO)
			hit->inter.normal = vec_opposite(hit->inter.normal);
		intensity = compute_local_light(rt, hit);
		color = vec_to_color(intensity * hit->inter.obj->color);
	}
	else
		color = rt->canvas.bg_color;

	return (color);
}
