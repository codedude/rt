/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:44:24 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 21:18:20 by mcasubol         ###   ########.fr       */
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
	ray_light->refraction = inter->obj->refraction;
}

t_vec		diffuse(t_rt *rt, t_object *obj, t_inter *inter, t_hit *light_hit)
{
	t_float		max_dist;
	t_vec		intensity;
//	t_ray		ray_refract;
//	t_inter		inter_refract;
	t_hit		refract;

	init_ray_light(&light_hit->ray, &max_dist, obj, inter);
	if (trace(rt, light_hit, max_dist) == SUCCESS)
	{
		intensity = VEC_ZERO;
		if (light_hit->inter.obj->refraction >= 1.0
			&& light_hit->inter.obj->transparency > 0.0)
		{
			refract.inter = *inter;
			refract.ray = refract_ray(light_hit->ray, *inter);
			if (trace(rt, &refract, FLOAT_MAX) == ERROR)
			{
				intensity += obj->intensity
					* light_hit->inter.obj->transparency;
			}
		}
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
	t_inter	inter;

	inter = hit->inter;
	intensity = VEC_ZERO;
	intensity_local = diffuse(rt, obj, &hit->inter, &light_hit);
	if (intensity_local[0] > 0.0 || intensity_local[1] > 0.0
		|| intensity_local[2] > 0.0)
	{
		if (vec_dot(vec_norm(light_hit.ray.dir), inter.normal) < FLOAT_ZERO
			&& inter.obj->transparency > 0)
			inter.normal *= -1;
		dot = vec_dot(vec_norm(light_hit.ray.dir), inter.normal);
		if (dot > FLOAT_ZERO)
		{
			intensity = intensity_local
				* (dot * inter.obj->phong[PHONG_KD]);
			if (inter.obj->phong[PHONG_SHINI] > 0.0)
			{
				reflect_ray = vec_norm((inter.normal * (-2.0 * dot))
					+ light_hit.ray.dir);
				dot = vec_dot(reflect_ray, hit->ray.dir);
				if (dot > FLOAT_ZERO)
				{
					intensity += intensity_local
						* (pow(dot, inter.obj->phong[PHONG_SHINI])
						* inter.obj->phong[PHONG_KS]);
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

t_vec		compute_color(t_rt *rt, t_hit *hit, int depth)
{
	t_vec		intensity;
	t_vec		color;
	t_vec		refract_color;
	t_float		kr;

	refract_color = VEC_ZERO;
	if (trace(rt, hit, FLOAT_MAX) == SUCCESS)
	{
		//return (hit->inter.obj->color);
		compute_hit_normal(&hit->ray, &hit->inter);
		if (hit->inter.obj->perturbation == WATER || hit->inter.obj->perturbation == WAVE)
			hit->inter.normal = normal_perturbation(hit->inter);
		compute_hit_biais(&hit->inter);
		if (vec_dot(hit->ray.dir, hit->inter.normal) > FLOAT_ZERO)
			hit->inter.normal *= -1.0;
		intensity = compute_local_light(rt, hit);
		if (hit->inter.obj->perturbation > 0)
			color = color_perturbation(hit->inter) * intensity;
	//	else if (hit->inter.obj->texture > 0)
	//		color = texture_color(hit->inter) * intensity;
		else
			color = intensity * hit->inter.obj->color;
		if (hit->inter.obj->reflexion > 0 && depth > 0)
			color = (1.0 - hit->inter.obj->reflexion) * color
				+ reflexion(rt, hit, depth) * hit->inter.obj->reflexion;
		if (hit->inter.obj->transparency > 0.0 && depth > 0
			&& hit->inter.obj->refraction >= 1.0)
		{
			kr = fresnel(hit->ray, hit->inter);
			if (kr < 1)
				refract_color = refract(rt, hit, depth);
			refract_color = (1.0 - kr) * refract_color
								+ kr * reflexion(rt, hit, depth);
			color = (1.0 - hit->inter.obj->transparency) * color
					+ refract_color * hit->inter.obj->transparency;
		}
	}
	else
		color = rt->canvas.bg_color;

	return (color);
}
