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

t_vec		from_to(t_vec from, t_vec to)
{
	t_vec	ret;

	ret.x = to.x - from.x;
	ret.y = to.y - from.y;
	ret.z = to.z - from.z;
	return (ret);
}

t_vec		scaling(t_vec vec, float a)
{
	t_vec	ret;

	ret.x = vec.x * a;
	ret.y = vec.y * a;
	ret.z = vec.z * a;
	return (ret);
}

t_vec		translation(t_vec vec, t_vec trans)
{
	vec.x += trans.x;
	vec.y += trans.y;
	vec.z += trans.z;
	return (vec);
}

t_vec		vec3_sub(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec		vec3_opposite(t_vec a)
{
	a.x *= -1.0;
	a.y *= -1.0;
	a.z *= -1.0;
	return (a);
}