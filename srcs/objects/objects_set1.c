/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/04/10 18:15:30 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "types.h"
#include "vec.h"

int		object_set_pos(t_object *obj, t_vec pos)
{
	obj->pos = pos;
	return (SUCCESS);
}

int		object_set_dir(t_object *obj, t_vec dir)
{
	obj->dir = dir;
	vec_norm(obj->dir);
	return (SUCCESS);
}

int		object_set_intensity(t_object *obj, t_vec intensity)
{
	obj->intensity = (t_vec){{
		clamp_f32(intensity.s[0], 0.0, 10.0),
		clamp_f32(intensity.s[1], 0.0, 10.0),
		clamp_f32(intensity.s[2], 0.0, 10.0),
		0.0}};
	return (SUCCESS);
}

int		object_set_color(t_object *obj, t_vec color)
{
	obj->color = (t_vec){{
		(t_float)clamp_i32(color.s[0], 0, 255) / 255.,
		(t_float)clamp_i32(color.s[1], 0, 255) / 255.,
		(t_float)clamp_i32(color.s[2], 0, 255) / 255.,
		0.0}};
	return (SUCCESS);
}

int		object_set_phong(t_object *obj, t_float phong[PHONGS])
{
	obj->phong[PHONG_SHINI] = round(
								clamp_f32(phong[PHONG_SHINI], 0.0, 1200.0));
	obj->phong[PHONG_KA] = clamp_f32(phong[PHONG_KA], 0.0, 1.0);
	obj->phong[PHONG_KD] = clamp_f32(phong[PHONG_KD], 0.0, 1.0);
	obj->phong[PHONG_KS] = clamp_f32(phong[PHONG_KS], 0.0, 1.0);
	return (SUCCESS);
}