/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/04/06 18:06:01 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "types.h"
#include "vec.h"

void		object_set_pos(t_object *obj, t_vec pos)
{
	obj->pos = pos;
}

void		object_set_dir(t_object *obj, t_vec dir)
{
	obj->dir = dir;
	vec_norm(obj->dir);
}

void		object_set_intensity(t_object *obj, t_vec intensity)
{
	obj->intensity = (t_vec){{
		clamp_float(intensity.s[0], 0.0, 10.0),
		clamp_float(intensity.s[1], 0.0, 10.0),
		clamp_float(intensity.s[2], 0.0, 10.0),
		0.0}};
}

void		object_set_color(t_object *obj, t_vec color)
{
	obj->color = (t_vec){{
		(t_float)clamp_int(color.s[0], 0, 255) / 255.,
		(t_float)clamp_int(color.s[1], 0, 255) / 255.,
		(t_float)clamp_int(color.s[2], 0, 255) / 255.,
		0.0}};
}

void		object_set_radius(t_object *obj, t_float radius)
{
	obj->radius = clamp_float(radius, 0.001, 10000.0);
	obj->radius2 = obj->radius * obj->radius;
}

void		object_set_phong(t_object *obj, t_float phong[PHONGS])
{
	obj->phong[PHONG_SHINI] = round(
								clamp_float(phong[PHONG_SHINI], 0.0, 1200.0));
	obj->phong[PHONG_KA] = clamp_float(phong[PHONG_KA], 0.0, 1.0);
	obj->phong[PHONG_KD] = clamp_float(phong[PHONG_KD], 0.0, 1.0);
	obj->phong[PHONG_KS] = clamp_float(phong[PHONG_KS], 0.0, 1.0);
}