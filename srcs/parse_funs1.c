/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:30:20 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 18:04:59 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "rt.h"
#include "parser.h"
#include "ft_math.h"
#include "types.h"

int		parse_t_width(void *data, char **strs)
{
	t_env	*env;
	int		n;

	env = (t_env *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	env->width = clamp_int(n, 32, 2500);
	return (SUCCESS);
}

int		parse_t_height(void *data, char **strs)
{
	t_env	*env;
	int		n;

	env = (t_env *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	env->height = clamp_int(n, 32, 1400);
	return (SUCCESS);
}

int		parse_t_background(void *data, char **strs)
{
	t_env	*env;
	int		n[3];

	env = (t_env *)data;
	if (ft_atoi_s(strs[0], &n[0]) == ERROR
		|| ft_atoi_s(strs[1], &n[1]) == ERROR
		|| ft_atoi_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	env->background = rgb_to_color(
		clamp_int(n[0], 0, 255),
		clamp_int(n[1], 0, 255),
		clamp_int(n[2], 0, 255));
	return (SUCCESS);
}

int		parse_t_ang(void *data, char **strs)
{
	t_env	*env;
	t_float	n[3];

	env = (t_env *)data;
	if (ft_atof_s(strs[0], &n[0]) == ERROR
		|| ft_atof_s(strs[1], &n[1]) == ERROR
		|| ft_atof_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	env->cam_ang = (t_vec){{
		clamp_float(n[0], -360.0, 360.0),
		clamp_float(n[1], -360.0, 360.0),
		clamp_float(n[2], -360.0, 360.0),
		0.0}};
	return (SUCCESS);
}

int		parse_t_fov(void *data, char **strs)
{
	t_env	*env;
	int		n;

	env = (t_env *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	env->fov = (t_f64)clamp_float(n, 1, 180);
	return (SUCCESS);
}
