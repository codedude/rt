/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/20 17:21:17 by vparis           ###   ########.fr       */
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

t_uint			compute_color(t_ray ray, int depth, t_rt *rt)
{
	t_inter		inter;
	t_uint		local;
	t_vec		intensity;
	

	closest_intersect(ray, LONG_MAX, rt->objects, &inter);
	local = BACKGROUND;
	/*if (inter.obj == NULL)
		return (BACKGROUND);
	intensity = light(inter, vec_opposite(ray.dir), rt);
	local = color_intensity(intensity, inter.obj->color);
	if (inter.obj->reflexion > 0)
	{
		local = calc_color((1.0 - inter.obj->reflexion), local)
		+ calc_color(inter.obj->reflexion, reflect(ray, rt, depth, inter));
		if (local > COLOR_MAX)
			return (COLOR_MAX);
	}
	if (inter.obj->transparency > 0 &&
		inter.obj->refraction >= 1.0)
		local = transmitted_light(ray, inter, depth, rt, local);*/
	return (local);
}

t_uint		transmitted_light(t_ray ray, t_inter inter, int depth, t_rt *rt, t_color local)
{
	t_float kr;
	t_uint		refraction_color;
	t_uint		reflected_color;

	kr = fresnel(ray, inter);
	refraction_color = 0;
	reflected_color = 0;
	if (kr < 1)
	{
		refraction_color = refract(ray, rt, depth, inter);
	}
	reflected_color = reflect(ray, rt, depth, inter);
	refraction_color = calc_color(1.0 - kr, refraction_color) + calc_color(kr, reflected_color);
	if (refraction_color > COLOR_MAX)
		refraction_color = COLOR_MAX;
	local = calc_color(1.0 - inter.obj->transparency, local) + calc_color(inter.obj->transparency, refraction_color);
	if (local > COLOR_MAX)
		return (COLOR_MAX);
	return (local);
}

t_uint		color_intensity(t_vec intensity, t_vec color)
{
	t_uint	ret;

	ret = rgb_to_color(color[0] * intensity[0], color[1] * intensity[1], color[2] * intensity[2]);
	return (ret);
}

t_uint		calc_color(t_float i, t_uint color)
{
	t_float	r;
	t_float	g;
	t_float	b;

	b = (color % 256);
	r = (color / (256 * 256));
	g = ((color / 256) - r * 256);
	b = b * i;
	r = r * i;
	g = g * i;
	if (r > 255)
		r = 255.0;
	if (r < 0)
		r = 0;
	if (g > 255)
		g = 255.0;
	if (g < 0)
		g = 0;
	if (b > 255)
		b = 255.0;
	if (b < 0)
		b = 0;
	return ((t_uint)(RGB((int)r, (int)g, (int)b)));
}
