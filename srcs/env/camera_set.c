/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:58:26 by valentin          #+#    #+#             */
/*   Updated: 2018/04/20 15:48:48 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "ft_math.h"
#include "types.h"
#include "rt.h"

int		camera_set_origin(t_rt *rt, t_vec v)
{
	rt->camera_update = 1;
	rt->camera.origin = v;
	return (SUCCESS);
}

int		camera_set_angle(t_rt *rt, t_vec v)
{
	rt->camera_update = 1;
	rt->camera.angle = (t_vec){
		fmodf(v[0], 360.0),
		fmodf(v[1], 360.0),
		fmodf(v[1], 360.0)};
	return (SUCCESS);
}

int		camera_set_fov(t_rt *rt, t_float fov)
{
	if (fov < 30.0 || fov > 120.0)
		return (ERROR);
	rt->camera_update = 1;
	rt->camera.fov = ft_tan(fov / 2.0);
	return (SUCCESS);
}
