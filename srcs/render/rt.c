/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/21 22:22:09 by valentin         ###   ########.fr       */
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

static int	compute_rt(t_rt *rt, t_uint *image, int y, int x)
{
	t_ray	ray;
	t_uint	color;

	ray = compute_primary_rays(x, y, rt->canvas, rt->camera);
	color = compute_color(ray, DEPTH, rt);
	ft_put_pixel(x, y, color, image, rt);
	return (SUCCESS);
}

int			rt(void *data)
{
	t_algo		*algo;
	int			i;
	int			j;

	algo = (t_algo *)data;
	i = algo->start;
	while (i < algo->end)
	{
		j = 0;
		while (j < algo->env->rt.canvas.width)
		{
			compute_rt(&(algo->env->rt), algo->env->sdl.image, i, j);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

t_ray 	compute_primary_rays(int x, int y, t_canvas canvas, t_camera camera)
{
	t_ray	ray;

	ray.dir[0] = ((t_float)x + 0.5) / (t_float)canvas.width;
	ray.dir[1] = ((t_float)y + 0.5) / (t_float)canvas.height;
	ray.dir[0] = (2.0 * ray.dir[0] - 1.0) * canvas.ratio[0];
	ray.dir[1] = (1.0 - 2.0 * ray.dir[1]) * canvas.ratio[1];
	ray.dir[2] = 1.0;
	vec_norm(ray.dir);
	ray.origin = camera.origin;
	ray.refraction = REFRACTION_INDEX;
	return (ray);
}

void	ft_put_pixel(int x, int y, t_uint color, t_uint *image, t_rt *rt)
{
	image[x + (y * rt->canvas.width)] = color;
}
