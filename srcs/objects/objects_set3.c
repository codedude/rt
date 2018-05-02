/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/04/25 02:50:37 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "types.h"
#include "vec.h"

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
