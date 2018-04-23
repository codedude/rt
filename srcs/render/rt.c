/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/23 18:29:38 by vparis           ###   ########.fr       */
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

static void	compute_primary_ray(int x, int y, t_rt *rt, t_ray *ray)
{
	ray->dir[0] = ((t_float)x + 0.5) / (t_float)rt->canvas.width;
	ray->dir[1] = ((t_float)y + 0.5) / (t_float)rt->canvas.height;
	ray->dir[0] = (2.0 * ray->dir[0] - 1.0) * rt->canvas.ratio[0];
	ray->dir[1] = (1.0 - 2.0 * ray->dir[1]) * rt->canvas.ratio[1];
	ray->dir[2] = 1.0;
	vec_norm(ray->dir);
	ray->origin = rt->camera.origin;
	ray->refraction = REFRACTION_INDEX;
}

static void	put_pixel(int pixel, t_uint color, t_uint *image)
{
	image[pixel] = color;
}

static int	compute_rt(t_rt *rt, t_uint *image, int y, int x)
{
	t_ray	ray;
	t_color	color;
	t_inter	inter;

	compute_primary_ray(x, y, rt, &ray);
	//Apply rotation on camera HERE
	if (trace(rt, &ray, &inter, FLOAT_MAX) == SUCCESS)
	{
		//color = compute_color(ray, MAX_DEPTH, rt);
		color = vec_to_color(inter.obj->color);
	}
	else
		color = rt->canvas.bg_color;
	put_pixel(x + (y * rt->canvas.width), color, image);
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
