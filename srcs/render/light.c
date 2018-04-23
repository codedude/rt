/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:10:20 by hcaillau          #+#    #+#             */
/*   Updated: 2018/04/11 16:25:50 by hcaillau         ###   ########.fr       */
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

t_vec				light(t_inter it, t_vec v, t_rt *rt)
{
	t_vec			i[4];
	t_ray			r;
	int 			j;

	i[0] = new_vec3(0.0, 0.0, 0.0);
	j = 0;
	while (j < rt->objects.size)
	{
		i[3].x = 1.0;
		if (rt->objects.objects_array[j].type == LIGHT_AMBIENT)
			i[0] += scaling(rt->objects.objects_array[j]->intensity, rt->objects.objects_array[j]->phong[PHONG_KA]);
		else
		{
			i[3].x = light_mid(&r, it, &j, rt);
			if (i[3].x < 0.000001)
				continue;
			if (dot(r.dir, it.normal) < 0
				&& rt->objects.object_array[it.id].transparency > 0)
				it.normal = vec3_opposite(it.normal);
			i[1].x = dot(it.normal, r.dir);
			i[2] = scaling(rt->objects.objects_array[j]->intensity, rt->objects.object_array[it.id].phong[PHONG_KD]);
			i[0] = vec3_add(i[0], scaling(light_specular(it, i, v, &r), i[3].x));
		}
		j++;
	}
	return (i[0]);
}

t_float					diffuse_light(t_ray *r, t_inter it, int *j,
		t_rt *rt)
{
	t_inter				inter;
	t_inter				transp_inter;
	t_ray				rayon;
	t_ray				refr_ray;

	if (rt->objects.objects_array[j].type == LIGHT_POINT)
	{
		r->dir = from_to(it.point, rt->objects.objects_array[j].dir);
		r->dir = vec3_normalize(r->dir);
		r->origin = it.point;
		rayon.origin = it.point;
		rayon.dir = r->dir;
		inter = closest_intersect(rayon, 0.000000001, 1.0, rt->objects);
	}
	else if (rt->objects.objects_array[j].type == LIGHT_PAR)
	{
		r->origin = it.point;
		r->dir = vec3_normalize(vec3_opposite(rt->objects.objects_array[j].dir);
		rayon.origin = it.point;
		rayon.dir = r->dir;
		inter = closest_intersect(rayon, 0.000000001, LONG_MAX, rt->objects);
	}
	if (inter.id >= 0)
	{·
		if (rt->objects.objects_array[inter.id].refraction >= 1.0
			&& rt->objects.objects_array[inter.id].transparency > 0)
		{
			transp_inter = inter;
			refr_ray = refract_ray(rayon, inter);
			inter = closest_intersect(refr_ray, 0.000000001, LONG_MAX, rt->objects);
			if (inter.id >= 0)
			{
				j++;
				return (0.0);
			}
			else
				return (rt->objects.objects_array[transp_inter.id].transparency);
		}
		else
			j++;
		return (0.0);
	}
	return (1.0);
}

t_vec				light_specular(t_inter it, t_vec i[4], t_vec v, t_ray *r, t_rt *rt)
{
	t_vec	ret;

	ret = 0;
	if (i[1].x > 0)
	{
		ret = scaling(i[2], i[1].x);
	if (it.shp->s > 0)
		{
			r->dir = vec3_sub(scaling(it.normal,
						dot(it.normal, r->dir) * 2.0), r->dir);
			i[1] = dot(r->dir, v);
			if (i[1].x > 0)
				ret += i[2] * pow(i[1].x / (vec_len(r->dir)
							* vec_len(v)), it.id.phong[PHONG_SHINI]);
		}
	}
	return (ret);
}
