/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:10:06 by valentin          #+#    #+#             */
/*   Updated: 2018/04/09 19:23:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "rt.h"
#include "parser.h"

/*
** Init all env at 0, init random, and parse file
*/

int			env_init(t_env *env, char *filename)
{
	char	**file;

	ft_bzero(env, sizeof(t_env));
	srand(time(NULL));
	if ((file = read_file(filename)) == NULL)
		return (ERROR);
	if (parse_file(env, file) == ERROR)
	{
		ft_strsplit_free(file);
		return (ERROR);
	}
	ft_strsplit_free(file);
	return (SUCCESS);
}

/*
** Reset env
*/

int			env_destroy(t_env *env)
{
	object_free(&env->objects);
	ft_bzero(env, sizeof(t_env));
	return (SUCCESS);
}
