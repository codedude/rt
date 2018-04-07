/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funs4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:12:06 by vparis            #+#    #+#             */
/*   Updated: 2018/04/07 18:17:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "ft_math.h"
#include "rt.h"
#include "objects.h"
#include "types.h"

int		parse_t_angle(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	(void)strs;
	obj = (t_object *)data;
	return (SUCCESS);
}

int		parse_t_size(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	(void)strs;
	obj = (t_object *)data;
	return (SUCCESS);
}

int		parse_t_reflexion(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	(void)strs;
	obj = (t_object *)data;
	return (SUCCESS);
}

int		parse_t_refraction(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	(void)strs;
	obj = (t_object *)data;
	return (SUCCESS);
}

int		parse_t_transparency(void *data, char **strs)
{
	t_object	*obj;
	t_float		n;

	(void)strs;
	obj = (t_object *)data;
	return (SUCCESS);
}
