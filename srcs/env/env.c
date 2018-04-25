/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:54:18 by vparis            #+#    #+#             */
/*   Updated: 2018/04/25 02:56:55 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "env.h"

#include "sdl_m.h"

int		env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(t_env));
	srand(time(NULL));
	if (rt_init(&env->rt, filename) == ERROR)
	{
		ft_putstr("Error : can't init rt\n");
		return (ERROR);
	}
	if (sdl_init(&env->sdl, env->rt.canvas.width, env->rt.canvas.height)
		== ERROR)
	{
		ft_putstr("Error : can't init sdl\n");
		return (ERROR);
	}
	if ((env->tp = tp_create(TP_AUTO_THREADS, TP_ON_START)) == NULL)
		return (ERROR);
	return (SUCCESS);
}

void	env_destroy(t_env *env)
{
	rt_destroy(&env->rt);
	sdl_destroy(&env->sdl);
	tp_destroy(&env->tp);
}
