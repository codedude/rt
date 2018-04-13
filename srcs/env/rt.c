/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:10:06 by valentin          #+#    #+#             */
/*   Updated: 2018/04/13 16:09:40 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
}

/*
** Init all env at 0, init random, and parse file
*/

t_rt		*rt_init(char *filename)
{
	t_rt	*rt;
	char	**file;

	if ((rt = (t_rt *)malloc(sizeof(t_rt))) == NULL)
		return (NULL);
	ft_bzero(rt, sizeof(t_rt));
	objects_init(&rt->objects);
	if ((file = read_file(filename)) == NULL)
		return (NULL);
	if (parse_file(rt, file) == ERROR)
	{
		ft_strsplit_free(file);
		return (NULL);
	}
	set_ratio(rt);
	ft_strsplit_free(file);
	return (rt);
}

/*
** Reset rt
*/

int			rt_destroy(t_rt **rt)
{
	objects_destroy(&(*rt)->objects);
	ft_bzero(*rt, sizeof(t_rt));
	*rt = NULL;
	return (SUCCESS);
}
