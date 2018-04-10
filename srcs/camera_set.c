/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:58:26 by valentin          #+#    #+#             */
/*   Updated: 2018/04/10 18:11:45 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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
		fmodf(v.s[0], 360.0),
		fmodf(v.s[1], 360.0),
		fmodf(v.s[1], 360.0)}};
	return (SUCCESS);
}

int		camera_set_fov(t_camera *camera, t_float fov)
{
	if (fov < 30.0 || fov > 120.0)
		return (ERROR);
	camera->fov = fov;
	return (SUCCESS);
}
