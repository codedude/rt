/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <hcaillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:52:02 by hcaillau          #+#    #+#             */
/*   Updated: 2018/05/03 20:03:50 by hcaillau         ###   ########.fr       */
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

void		surface_color(t_hit *hit, t_vec intensity, t_vec *color)
{	
	if (hit->inter.obj->perturbation > 0)
		*color = color_perturbation(hit->inter) * intensity;
	else if (hit->inter.obj->texture.pixels != NULL)
		*color = texture_color(hit->inter) * intensity;
	else
		*color = intensity * hit->inter.obj->color;
}

void		light_effect(t_hit *hit, t_vec *color, int depth, t_rt *rt)
{
	t_vec		refract_color;
	t_float		kr;

	kr = 0.0;
	refract_color = VEC_INIT(0.0, 0.0, 0.0);
	if (hit->inter.obj->reflexion > 0 && depth > 0)
		color = (1.0 - hit->inter.obj->reflexion) * color
				+ reflexion(rt, hit, depth) * hit->inter.obj->reflexion;
	if (hit->inter.obj->transparency > 0.0 && depth > 0
			&& hit->inter.obj->refraction >= 1.0)
	{
		kr = fresnel(hit->ray, hit->inter);
		if (kr < 1)
			refract_color = refract(rt, hit, depth);
		refract_color = (1.0 - kr) * refract_color
					+ kr * reflexion(rt, hit, depth);
		color = (1.0 - hit->inter.obj->transparency) * color
					+ refract_color * hit->inter.obj->transparency;
	}
}