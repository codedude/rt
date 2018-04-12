/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:54:18 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 15:13:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "env.h"
#include "opencl.h"

int		env_init(t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	srand(time(NULL));
	if (opencl_init(&env->opencl) == ERROR)
	{
		ft_putstr("Error : can't init opencl\n");
		return (ERROR);
	}
	return (SUCCESS);
}

void	env_destroy(t_env *env)
{
	opencl_destroy(&env->opencl);
}
