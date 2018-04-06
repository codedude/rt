/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:52:32 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 18:13:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "rt.h"
#include "objects.h"
#include "parser.h"

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
	{
		ft_putstr("rt : ./rtv1 SCENE\n");
		return (EXIT_SUCCESS);
	}
	if (parse_map(&env, argv[1]) == ERROR)
		return (ERROR);
	object_free(&env.objects);
	return (EXIT_SUCCESS);
}
