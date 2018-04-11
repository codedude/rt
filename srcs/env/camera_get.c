/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:58:26 by valentin          #+#    #+#             */
/*   Updated: 2018/04/09 19:31:44 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "rt.h"

t_vec	camera_get_origin(t_camera *camera)
{
	return (camera->origin);
}

t_vec	camera_get_angle(t_camera *camera)
{
	return (camera->angle);
}

t_float	camera_get_fov(t_camera *camera)
{
	return (camera->fov);
}
