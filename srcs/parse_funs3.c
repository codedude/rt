/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 20:45:34 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 18:02:01 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "ft_math.h"
#include "rt.h"
#include "objects.h"
#include "types.h"

int			parse_t_orig(void *data, char **strs)
{
	t_env	*env;
	t_float	n[3];

	env = (t_env *)data;
	if (ft_atof_s(strs[0], &n[0]) == ERROR
		|| ft_atof_s(strs[1], &n[1]) == ERROR
		|| ft_atof_s(strs[2], &n[2]) == ERROR)
		return (ERROR);
	env->cam_orig = (t_vec){{n[0], n[1], n[2], 0.0}};
	return (SUCCESS);
}

int			parse_t_phong(void *data, char **strs)
{
	t_object	*obj;
	t_float		phong[PHONGS];
	int			shini;

	obj = (t_object *)data;
	if (ft_atoi_s(strs[0], &shini) == ERROR
		|| ft_atof_s(strs[1], &phong[PHONG_KA]) == ERROR
		|| ft_atof_s(strs[2], &phong[PHONG_KD]) == ERROR
		|| ft_atof_s(strs[3], &phong[PHONG_KS]) == ERROR)
		return (ERROR);
	phong[PHONG_SHINI] = (t_float)shini;
	object_set_phong(obj, phong);
	return (SUCCESS);
}