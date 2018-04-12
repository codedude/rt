/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:10:06 by valentin          #+#    #+#             */
/*   Updated: 2018/04/12 14:57:54 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "rt.h"
#include "parser.h"

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
