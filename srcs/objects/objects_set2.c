/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_set2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 15:56:49 by valentin          #+#    #+#             */
/*   Updated: 2018/04/25 02:50:33 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "objects.h"
#include "types.h"
#include "vec.h"

int		object_set_radius(t_object *obj, t_float n)
{
	obj->radius = clamp_f64(n, 0.001, 10000.0);
	obj->radius2 = obj->radius * obj->radius;
	return (SUCCESS);
}

int		object_set_angle(t_object *obj, t_float n)
{
	obj->angle = fmod(n, 360.0);
	return (SUCCESS);
}

int		object_set_size(t_object *obj, t_float n)
{
	obj->size = clamp_f64(n, -10000.0, 10000.0);
	return (SUCCESS);
}

int		object_set_matrix(t_object *obj, t_vec rot)
{
	t_vec	x[3];
	t_vec	y[3];
	t_vec	z[3];
	t_vec	tmp[3];
	t_vec	matrix[3];

	matrix_rotx(x, rot.x);
	matrix_roty(y, rot.y);
	matrix_rotz(z, rot.z);
	matrix_mul_matrix(x, y, tmp);
	matrix_mul_matrix(tmp, z, matrix);
	obj->obj_to_w = obj_to_w;
	object_set_inverse_matrix(obj, (-1) * rot);
	return (SUCCESS);
}

int		object_set_inverse_matrix(t_object *obj, t_vec rot)
{
	t_vec	x[3];
	t_vec	y[3];
	t_vec	z[3];
	t_vec	tmp[3];
	t_vec	matrix[3];

	matrix_rotx(x, rot.x);
	matrix_roty(y, rot.y);
	matrix_rotz(z, rot.z);
	matrix_mul_matrix(x, y, tmp);
	matrix_mul_matrix(tmp, z, matrix);
	obj->w_to_obj = w_to_obj;
	return (SUCCESS);
}