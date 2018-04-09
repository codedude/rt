/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:58:26 by valentin          #+#    #+#             */
/*   Updated: 2018/04/09 19:29:08 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "rt.h"

int		camera_set_origin(t_camera *camera, t_vec v)
{
	camera->origin = v;
	return (SUCCESS);
}

int		camera_set_angle(t_camera *camera, t_vec v)
{
	camera->angle = (t_vec){{
		clamp_f32(v.s[0], -360.0, 360.0),
		clamp_f32(v.s[1], -360.0, 360.0),
		clamp_f32(v.s[2], -360.0, 360.0)}};
	return (SUCCESS);
}

int		camera_set_fov(t_camera *camera, t_float fov)
{
	if (fov < 30.0 || fov > 120.0)
		return (ERROR);
	camera->fov = fov;
	return (SUCCESS);
}
