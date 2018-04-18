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

t_vec			pixel_to_dir(__constant t_canvas *canvas,
								t_float fov, t_int x, t_int y)
{
	t_vec	dir;

	dir.x = ((t_float)x + 0.5) / (t_float)canvas->width;
	dir.y = ((t_float)y + 0.5) / (t_float)canvas->height;
	dir.x = (2.0 * dir.x - 1.0) * fov * canvas->ratio[0];
	dir.y = (1.0 - 2.0 * dir.y) * fov * canvas->ratio[1];
	dir.z = 1.0;
	normalize(dir);
	return (dir);
}

__kernel void	primary_rays(__constant t_canvas *canvas,
							__constant t_camera *camera,
							__global t_ray *rays)
{
	int		x, y;
	t_ray	ray;

	x = get_global_id(1);
	y = get_global_id(0);
	ray.origin = camera->origin;
	ray.refraction = 1.0;
	ray.dir = pixel_to_dir(canvas, camera->fov, x, y);
	rays[y * canvas->width + x] = ray;
}
