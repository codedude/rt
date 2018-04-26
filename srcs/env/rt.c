/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:10:06 by valentin          #+#    #+#             */
/*   Updated: 2018/04/26 16:01:06 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_math.h"
#include "libft.h"
#include "rt.h"
#include "parser.h"

static void	set_ratio(t_rt *rt)
{
	if (rt->canvas.width > rt->canvas.height)
	{
		rt->canvas.ratio[0] =
		(t_float)rt->canvas.width / (t_float)rt->canvas.height;
		rt->canvas.ratio[1] = 1.0;
	}
	else if (rt->canvas.height > rt->canvas.width)
	{
		rt->canvas.ratio[0] = 1.0;
		rt->canvas.ratio[1] =
		(t_float)rt->canvas.height / (t_float)rt->canvas.width;
	}
	else
	{
		rt->canvas.ratio[0] = 1.0;
		rt->canvas.ratio[1] = 1.0;
	}
	rt->canvas.ratio[0] *= ft_tan(rt->camera.fov / 2.0);
	rt->canvas.ratio[1] *= ft_tan(rt->camera.fov / 2.0);
	rt->canvas_update = 1;
}

/*
** Init all env at 0, init random, and parse file
*/

int			rt_init(t_rt *rt, char *filename)
{
	char	**file;

	ft_bzero(rt, sizeof(t_rt));
	objects_init(&rt->objects);
	if ((file = read_file(filename)) == NULL)
		return (ERROR);
	if (parse_file(rt, file) == ERROR)
	{
		ft_strsplit_free(file);
		return (ERROR);
	}
	set_ratio(rt);
	objects_gen_array(&rt->objects);
	ft_strsplit_free(file);
	return (SUCCESS);
}

/*
** Reset rt
*/

int			rt_destroy(t_rt *rt)
{
	objects_destroy(&rt->objects);
	ft_bzero(rt, sizeof(t_rt));
	return (SUCCESS);
}
