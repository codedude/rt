/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:08:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/23 19:11:01 by vparis           ###   ########.fr       */
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

t_vec		vec_scalar(t_vec v1, t_float n)
{
	t_vec	r;

	r[0] = v1[0] * n;
	r[1] = v1[1] * n;
	r[2] = v1[2] * n;
	return (r);
}

void		vec_opposite(t_vec v1)
{
	v1[0] *= -1.0;
	v1[1] *= -1.0;
	v1[2] *= -1.0;
}
