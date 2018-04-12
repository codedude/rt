/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:52:32 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 15:19:39 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "parser.h"
#include "opencl.h"

/*
** rt + opencl_init_buffers se fait pour chaque fichier
*/

int			main(int argc, char **argv)
{
	t_env		env;
	t_rt		*rt;

	if (argc < 2)
	{
		ft_putstr("rt : ./rtv1 SCENE\n");
		return (EXIT_FAILURE);
	}
	if (env_init(&env) == ERROR)
		return (EXIT_FAILURE);
	if ((rt = rt_init(argv[1])) == NULL)
	{
		ft_putstr("Error : can't init env\n");
		return (EXIT_FAILURE);
	}
	if (opencl_init_buffers(&env.opencl, rt) == ERROR)
	{
		ft_putstr("Error : can't init opencl\n");
		return (ERROR);
	}
	rt_destroy(&rt);
	env_destroy(&env);
	return (EXIT_SUCCESS);
}
