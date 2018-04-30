/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 18:19:44 by vparis            #+#    #+#             */
/*   Updated: 2018/04/30 18:44:09 by vparis           ###   ########.fr       */
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

int		manage_binds(SDL_Event *event, t_env *env, int *update)
{
	t_vec		cam_pos;
	const		Uint8 *state;

	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);
	SDL_PollEvent(event);
	if (event->type == SDL_QUIT)
		return (0);
	if (state[SDL_SCANCODE_ESCAPE])
		return (0);
	if (event->type == SDL_KEYDOWN)
	{
		*update = 1;
		cam_pos = camera_get_origin(&env->rt);
		if (state[SDL_SCANCODE_RIGHT])
			cam_pos[0] += 1.0;
		else if (state[SDL_SCANCODE_LEFT])
			cam_pos[0] -= 1.0;
		else if (state[SDL_SCANCODE_UP])
			cam_pos[1] += 1.0;
		else if (state[SDL_SCANCODE_DOWN])
			cam_pos[1] -= 1.0;
		else if (state[SDL_SCANCODE_Z])
			cam_pos[2] -= 1.0;
		else if (state[SDL_SCANCODE_X])
			cam_pos[2] += 1.0;
		else if (state[SDL_SCANCODE_F])
		{
			if (env->show_fps != 1)
				env->show_fps = 1;
		}
		else if (state[SDL_SCANCODE_D])
		{
			t_id id = env->rt.objects.objects_lst->object->id;
			object_del(&(env->rt.objects), id);
		}
		else if (state[SDL_SCANCODE_S])
		{
			if (env->save_img != 1)
			{
				save_img(env->sdl.image, env->rt.canvas.width,
					env->rt.canvas.height);
				env->save_img = 1;
			}
		}
		else
			*update = 0;
		if (*update == 1)
		{
			camera_set_origin(&env->rt, cam_pos);
			render_update(env);
		}
	}
	else if (event->type == SDL_KEYUP)
	{
		if (state[SDL_SCANCODE_F] == 0)
		{
			env->show_fps = 1;
		}
		else if (state[SDL_SCANCODE_S] == 0)
			env->save_img = 0;
	}

	return (1);
}
