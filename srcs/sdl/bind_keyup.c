/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_keyup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:25:39 by vparis            #+#    #+#             */
/*   Updated: 2018/05/01 17:35:21 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "render.h"
#include "bmp.h"

static int	manage_binds_up_3(SDL_Event *event, t_env *env, int *update)
{
	if (event->key.keysym.sym == KEY_RELOAD)
	{
		if (rt_reload(&env->rt) == SUCCESS)
		{
			if (sdl_resize(&env->sdl, env->rt.canvas.width,
				env->rt.canvas.height) == ERROR)
				return (-1);
			ft_putendl("Scene reloaded");
			*update = 1;
		}
	}
	return (1);
}

static int	manage_binds_up_2(SDL_Event *event, t_env *env, int *update)
{
	if (event->key.keysym.sym == KEY_AALIAS)
	{
		env->rt.antialias = !env->rt.antialias;
		if (env->rt.antialias)
			ft_putendl("Anti-aliasing activated");
		else
			ft_putendl("Anti-aliasing deactivated");
	}
	else if (event->key.keysym.sym == KEY_SEPIA)
	{
		env->rt.sepia = !env->rt.sepia;
		if (env->rt.sepia)
			ft_putendl("Sepia mode activated");
		else
			ft_putendl("Sepia mode deactivated");
	}
	else
		return (manage_binds_up_3(event, env, update));
	return (1);
}

int			manage_binds_up(SDL_Event *event, t_env *env, int *update)
{
	if (event->key.keysym.sym == KEY_ESCAPE)
	{
		ft_putendl("Exiting...");
		return (0);
	}
	else if (event->key.keysym.sym == KEY_FPS)
	{
		env->show_fps = !env->show_fps;
		if (env->show_fps)
			ft_putendl("FPS activated");
		else
			ft_putendl("FPS deactivated");
	}
	else if (event->key.keysym.sym == KEY_SAVE)
	{
		if (save_img(env->sdl.image, env->rt.canvas.width,
				env->rt.canvas.height) == ERROR)
			ft_putstr("Error : can't save image\n");
	}
	else
		return (manage_binds_up_2(event, env, update));
	return (1);
}
