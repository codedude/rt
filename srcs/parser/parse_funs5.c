/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:30:18 by mcasubol          #+#    #+#             */
/*   Updated: 2018/05/02 17:21:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "ft_math.h"
#include "rt.h"
#include "objects.h"
#include "types.h"
#include "vec.h"

int				parse_t_limited(void *data, char **strs)
{
	t_object	*obj;
	int			n;
	t_float		o[3];
	t_float		p[3];

	obj = (t_object*)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	obj->is_limited = n;
	if (ft_atof_s(strs[1], &o[0]) == ERROR
		|| ft_atof_s(strs[2], &p[0]) == ERROR
		|| ft_atof_s(strs[3], &o[1]) == ERROR
		|| ft_atof_s(strs[4], &p[1]) == ERROR
		|| ft_atof_s(strs[5], &o[2]) == ERROR
		|| ft_atof_s(strs[6], &p[2]) == ERROR)
		return (ERROR);
	obj->lower_limit = VEC_INIT(o[0], o[1], o[2]);
	obj->upper_limit = VEC_INIT(p[0], p[1], p[2]);
	return (SUCCESS);
}

int				parse_t_texture(void *data, char **strs)
{
	t_object	*obj;
	int			n;

	obj = (t_object *)data;
	if (ft_atoi_s(strs[0], &n) == ERROR)
		return (ERROR);
	return (object_set_texture(obj, n));
}
