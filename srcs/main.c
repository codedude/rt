/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:52:32 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 19:24:35 by vparis           ###   ########.fr       */
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
#include "vec.h"

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
	{
		ft_putstr("rt : ./rtv1 SCENE\n");
		return (EXIT_FAILURE);
	}
	if (env_init(&env, argv[1]) == ERROR)
		return (EXIT_FAILURE);
	loop(&env);
	env_destroy(&env);
	return (EXIT_SUCCESS);
}
