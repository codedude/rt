/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:52:32 by vparis            #+#    #+#             */
/*   Updated: 2018/04/10 18:15:06 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "rt.h"
#include "objects.h"
#include "parser.h"

int			main(int argc, char **argv)
{
	t_env	*env;

	if (argc < 2)
	{
		ft_putstr("rt : ./rtv1 SCENE\n");
		return (EXIT_FAILURE);
	}
	if ((env = env_init(argv[1])) == NULL)
	{
		ft_putstr("Error : can't init env\n");
		return (EXIT_FAILURE);
	}
	object_gen_array(&env->objects);
	env_destroy(&env);
	return (EXIT_SUCCESS);
}
