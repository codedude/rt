/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_rays.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:30:15 by vparis            #+#    #+#             */
/*   Updated: 2018/04/11 18:30:42 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "rt.h"

void		raster_to_ndc(__float2 *v, t_float width, t_float height)
{
	if (width <= 0.0 || height <= 0.0)
		*v = (__float2)(0.0, 0.0);
	else
	{
		v->x = (v->x + 0.5) / width;
		v->y = (v->y + 0.5) / height;
	}
}

void		ndc_to_cam_coord(__float2 v, t_vec *vec, t_float fov,
							t_float aspect_ratio)
{
	t_float	ang;

	ang = (DEG_TO_RAD * fov) / 2.0;
	vec->x = (2.0 * v.x - 1.0) * tan(ang) * aspect_ratio;
	vec->y = (1.0 - 2.0 * v.y) * tan(ang);
	vec->z = 1;
}

void		pixel_to_ray_in_world(__constant t_camera *camera,
				__constant t_canvas *canvas, t_ray *ray,
				t_float x, t_float y)
{
	__float2	v;
	t_vec		vec;

	v = (__float2)(x, y);
	raster_to_ndc(&v, (t_float)canvas->width, (t_float)canvas->height);
	ndc_to_cam_coord(v, &vec, camera->fov, ((t_float)canvas->width / (t_float)canvas->height));
	vec = vec + camera->origin;
	ray->origin = camera->origin;
	ray->dir = vec - ray->origin;
	ray->refraction = 1.0;
}

__kernel void primary_rays(__constant t_canvas *canvas,
							__constant t_camera *camera, __global t_ray *rays)
{
	int		gid;
	int		x;
	int		y;
	t_ray	ray;

	gid = get_global_id(0);
	x = gid % canvas->width;
	y = gid / canvas->width;
	pixel_to_ray_in_world(camera, canvas, &ray, x, y);
	rays[gid] = ray;
}
