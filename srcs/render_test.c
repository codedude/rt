/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:29:36 by vparis            #+#    #+#             */
/*   Updated: 2018/04/18 15:10:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <OpenCL/OpenCL.h>
#include <assert.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "opencl.h"

void		loop(t_env *env)
{
	int			loop;
	int			update;
	int			show_fps;
	SDL_Event	event;
	t_vec		cam_pos;

	loop = 1;
	update = 1;
	show_fps = 0;
	while (loop == 1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			loop = 0;
		if (event.type == SDL_KEYDOWN)
		{
			cam_pos = camera_get_origin(&env->rt);
			if (event.key.keysym.sym == SDLK_ESCAPE)
				loop = 0;
			else if (event.key.keysym.sym == SDLK_RIGHT)
				cam_pos.s[0] += 1.0;
			else if (event.key.keysym.sym == SDLK_LEFT)
				cam_pos.s[0] -= 1.0;
        	else if (event.key.keysym.sym == SDLK_UP)
				cam_pos.s[1] += 1.0;
        	else if (event.key.keysym.sym == SDLK_DOWN)
				cam_pos.s[1] -= 1.0;
			else if (event.key.keysym.sym == SDLK_f)
				show_fps = !show_fps;
			else if (event.key.keysym.sym == SDLK_d)
			{
				t_id id = env->rt.objects.objects_lst->object->id;
				object_del(&(env->rt.objects), id);
			}
			camera_set_origin(&env->rt, cam_pos);
			opencl_update_buffers(&env->opencl, &env->rt);
        	update = 1;
		}
		if (update == 1 || 1)
		{
			if (opencl_run_program(&env->opencl, &env->rt, &env->sdl) == ERROR)
			{
				printf("Rendering error\n");
				break ;
			}
			sdl_render(&env->sdl);
			get_fps(show_fps, 1);
			update = 0;
		}
	}
}
