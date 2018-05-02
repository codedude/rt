/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcasubol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 11:03:06 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/02 17:45:01 by mcasubol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float			intersect_cube(t_ray *ray, t_object *obj, t_float *t)
{
	t_vec		inter;
	t_float		u[6];

	*t = -1;
	u[0] = -(ray->origin.z / ray->dir.z);
	u[1] = -(ray->origin.y / ray->dir.y);
	u[2] = -(ray->origin.x / ray->dir.x);
	u[3] = (obj->side - ray->origin.z) / ray->dir.z;
	u[4] = (obj->side - ray->origin.y) / ray->dir.y;
	u[5] = (obj->side - ray->origin.x) / ray->dir.x;
	inter = ray->origin + ray->dir * u[0];
	if (!(inter.x < 0 || inter.x > obj->side || inter.y < 0 || inter.y > obj->side) && (u[0] < *t || *t == -1))
		*t = u[0];
	inter = ray->origin + ray->dir * u[1];
	if (!(inter.x < 0 || inter.x > obj->side || inter.z < 0 || inter.z > obj->side) && (u[1] < *t || *t == -1))
		*t = u[1];
	inter = ray->origin + ray->dir * u[2];
	if (!(inter.z < 0 || inter.z > obj->side || inter.y < 0 || inter.y > obj->side) && (u[2] < *t || *t == -1))
		*t = u[2];
	inter = ray->origin + ray->dir * u[3];
	if (!(inter.x < 0 || inter.x > obj->side || inter.y < 0 || inter.y > obj->side) && (u[3] < *t || *t == -1))
		*t = u[3];
	inter = ray->origin + ray->dir * u[4];
	if (!(inter.x < 0 || inter.x > obj->side || inter.z < 0 || inter.z > obj->side) && (u[4] < *t || *t == -1))
		*t = u[4];
	inter = ray->origin + ray->dir * u[5];
	if (!(inter.z < 0 || inter.z > obj->side || inter.y < 0 || inter.y > obj->side) && (u[5] < *t || *t == -1))
		*t = u[5];

	return (SUCCESS);
}

void			norm_cube(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	inter->normal = VEC_INIT(0.0, 0.0, 1.0);
}
