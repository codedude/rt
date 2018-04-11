/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:10:06 by valentin          #+#    #+#             */
/*   Updated: 2018/04/10 17:59:37 by vparis           ###   ########.fr       */
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

t_env		*env_init(char *filename)
{
	t_env	*env;
	char	**file;

	if ((env = (t_env *)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	ft_bzero(env, sizeof(t_env));
	srand(time(NULL));
	if ((file = read_file(filename)) == NULL)
		return (NULL);
	if (parse_file(env, file) == ERROR)
	{
		ft_strsplit_free(file);
		return (NULL);
	}
	ft_strsplit_free(file);
	return (env);
}

/*
** Reset env
*/

int			env_destroy(t_env **env)
{
	object_destroy(&(*env)->objects);
	ft_bzero(*env, sizeof(t_env));
	*env = NULL;
	return (SUCCESS);
}
