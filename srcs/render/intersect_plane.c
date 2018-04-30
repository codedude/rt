/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:32:55 by vparis            #+#    #+#             */
/*   Updated: 2018/04/26 16:41:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "objects.h"
#include "vec.h"
#include "render.h"
#include "rt.h"

t_float		intersect_plane(t_ray *ray, t_object *obj, t_float *t)
{
	(void)obj;
	if (ray->dir.z == 0.0)
		return(-1.0);
	*t = -(ray->origin.z / ray->dir.z);
	return (SUCCESS);
}

void		norm_plane(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	inter->normal = VEC_INIT(0.0, 0.0, 1.0);
}
