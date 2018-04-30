/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:29:36 by vparis            #+#    #+#             */
/*   Updated: 2018/04/30 16:55:12 by vparis           ###   ########.fr       */
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
	t_vec		cam_pos;

	loop = 1;
	update = 1;
	while (loop == 1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			loop = 0;
		if (event.type == SDL_KEYDOWN)
		{
			cam_pos = camera_get_origin(&env->rt);
			if (event.key.keysym.sym == SDLK_ESCAPE)
				break ;
			else if (event.key.keysym.sym == SDLK_RIGHT)
				cam_pos[0] += 1.0;
			else if (event.key.keysym.sym == SDLK_LEFT)
				cam_pos[0] -= 1.0;
        	else if (event.key.keysym.sym == SDLK_UP)
				cam_pos[1] += 1.0;
        	else if (event.key.keysym.sym == SDLK_DOWN)
				cam_pos[1] -= 1.0;
			else if (event.key.keysym.sym == SDLK_z)
				cam_pos[2] -= 3.0;
			else if (event.key.keysym.sym == SDLK_x)
				cam_pos[2] += 3.0;
			else if (event.key.keysym.sym == SDLK_f)
				env->show_fps = !env->show_fps;
			else if (event.key.keysym.sym == SDLK_s)
				save_img(env->sdl.image, env->rt.canvas.width,
					env->rt.canvas.height);
			else if (event.key.keysym.sym == SDLK_d)
			{
				t_id id = env->rt.objects.objects_lst->object->id;
				object_del(&(env->rt.objects), id);
			}
			camera_set_origin(&env->rt, cam_pos);
			render_update(env);
        	update = 1;
		}
		if (update == 1)
		{
			render_compute(env);
			sdl_render(&env->sdl);
			get_fps(env->show_fps, 1);
			update = 0;
		}
	}
}
