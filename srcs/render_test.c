/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:29:36 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 13:14:47 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "render.h"
#include "bmp.h"

void		loop(t_env *env)
{
	int			loop;
	int			update;
	SDL_Event	event;

	loop = 1;
	update = 1;
	render_compute(env);
	sdl_render(&env->sdl);
	while (loop == 1)
	{
		loop = manage_binds(&event, env, &update);
		if (loop == -1)
			break ;
		if (update == 1)
		{
			if (render_update(env) == ERROR)
				break ;
			render_compute(env);
			sdl_render(&env->sdl);
			get_fps(env->show_fps, 1);
			update = 0;
		}
	}
}
