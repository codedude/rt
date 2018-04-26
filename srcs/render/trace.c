/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:14:14 by vparis            #+#    #+#             */
/*   Updated: 2018/04/26 14:41:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

void		compute_hit_normal(t_ray *ray, t_inter *inter)
{
	if (inter->obj->type == PLANE)
		norm_plane(ray, inter->obj, inter);
	else if (inter->obj->type == SPHERE)
		norm_sphere(ray, inter->obj, inter);
}

t_float		intersect(t_ray *ray, t_object *obj)
{
	t_float		t;

	t = FLOAT_ZERO;
	if (obj->type == PLANE)
		intersect_plane(ray, obj, &t);
	else if (obj->type == SPHERE)
		intersect_sphere(ray, obj, &t);
	return (t);
}

int			trace(t_rt *rt, t_ray *ray, t_inter *inter, t_float max_inter)
{
	t_object	*objs;
	int			i;
	t_float		t;

	inter->t = FLOAT_MAX;
	inter->obj = NULL;
	objs = rt->objects.objects_array;
	i = 0;
	while (i < rt->objects.size)
	{
		if ((t = intersect(ray, &objs[i])) > FLOAT_MIN)
		{
			if (t < inter->t && t < max_inter)
			{
				inter->t = t;
				inter->obj = &objs[i];
			}
		}
		i++;
	}
	return (inter->obj == NULL ? ERROR : SUCCESS);
}
