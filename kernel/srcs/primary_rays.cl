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

void		raster_to_ndc(__float2 *v, float width, float height)
{
	if (width <= 0 || height <= 0)
		*v = (__float2)(0, 0);
	else
	{
		v->x = (v->x + 0.5) / width;
		v->y = (v->y + 0.5) / height;
	}
}

float		ft_torad(float n)
{
	return ((n * M_PI) / 180);
}

void		ndc_to_cam_coord(__float2 v, __float3 *vec, float aspect_ratio)
{
	vec->x = (2 * v.x - 1) * tan(ft_torad(CAM_FOV / 2.0)) * aspect_ratio;
	vec->y = (1 - 2 * v.y) * tan(ft_torad(CAM_FOV / 2.0));
	vec->z = CAM_FOCUS;
}

void		pixel_to_ray_in_world(t_ray *ray, __constant t_cam *cam, float x, float y)
{
	__float2	v;
	__float3	vec;

	v = (__float2)(x, y);
	raster_to_ndc(&v, cam->width, cam->height);
	ndc_to_cam_coord(v, &vec, cam->aspect_ratio);
	vec = vec + cam->origin;
	ray->origin = cam->origin;
	ray->dir = vec - ray->origin;
	ray->refr = 1.0;
}

__kernel void render_kernel(__global t_ray *rays, __constant t_cam *cam)
{
	int		gid;
	int		x;
	int		y;
	t_ray	ray;
	gid = get_global_id(0);
	x = gid % cam->width;
	y = gid / cam->width;
	pixel_to_ray_in_world(&ray, cam, x, y);
	rays[gid] = ray;
}
