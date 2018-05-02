/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:32:55 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 20:25:23 by mcasubol         ###   ########.fr       */
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
	*t = -(ray->origin.y / ray->dir.y);
	obj->t2[0] = *t;
	obj->t2[1] = FLOAT_MAX;
	return (SUCCESS);
}

void		norm_plane(t_ray *ray, t_object *obj, t_inter *inter)
{
	(void)ray;
	(void)obj;
	inter->normal = VEC_INIT(0.0, 1.0, 0.0);
}
