/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/05/02 17:32:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "types.h"
#include "vec.h"
#include "sdl_m.h"

int		object_set_reflexion(t_object *obj, t_float n)
{
	obj->reflexion = clamp_f64(n, 0.0, 1.0);
	return (SUCCESS);
}

int		object_set_refraction(t_object *obj, t_float n)
{
	obj->refraction = clamp_f64(n, 0.0, 10.0);
	return (SUCCESS);
}

int		object_set_transparency(t_object *obj, t_float n)
{
	obj->transparency = clamp_f64(n, 0.0, 1.0);
	return (SUCCESS);
}

int		object_set_perturbation(t_object *obj, int n)
{
	if (n < 0 || n > 10)
		return (ERROR);
	obj->perturbation = n;
	return (SUCCESS);
}

int		object_set_texture(t_object *obj, int n)
{
	if (n < 0 || n > 10)
		return (ERROR);
	if (n == 0)
		obj->texture = NULL;
	else
		obj->texture = sdl_get_texture(n);
	return (SUCCESS);
}
