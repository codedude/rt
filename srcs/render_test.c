/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:29:36 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 17:20:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "opencl.h"

int			run_cl(t_env *env, t_rt *rt, SDL_Surface *screen)
{
	cl_int	err;
	size_t	global_work_size;
	size_t	buffer_size;

	global_work_size = rt->canvas.size;
	buffer_size = sizeof(t_ray) * global_work_size;
	err = clEnqueueNDRangeKernel(env->opencl.cmd_queue, env->opencl.kernels[0],
							1, NULL, &global_work_size, NULL, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		return (ERROR);
	clFinish(env->opencl.cmd_queue);
	err = clEnqueueReadBuffer(env->opencl.cmd_queue, env->opencl.buffers.screen,
		CL_TRUE, 0, sizeof(Uint32) * rt->canvas.size, (Uint32 *)screen->pixels,
		0, NULL, NULL);
	if (err != CL_SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

void		loop(t_env *env, t_rt *rt, SDL_Window *window,
	SDL_Surface *screen)
{
	int			loop;
	int			update;
	SDL_Event	event;
	t_vec		cam_pos;

	loop = 1;
	update = 1;
	while (loop == 1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			loop = 0;
		if (event.type == SDL_KEYDOWN)
		{
			cam_pos = camera_get_origin(&rt->camera);
			if (event.key.keysym.sym == SDLK_ESCAPE)
				loop = 0;
			else if (event.key.keysym.sym == SDLK_RIGHT)
				cam_pos.s[0] += 2;
			else if (event.key.keysym.sym == SDLK_LEFT)
				cam_pos.s[0] -= 2;
        	else if (event.key.keysym.sym == SDLK_UP)
				cam_pos.s[1] += 2;
        	else if (event.key.keysym.sym == SDLK_DOWN)
				cam_pos.s[1] -= 2;
			camera_set_origin(&rt->camera, cam_pos);
			opencl_update_camera(&env->opencl, rt);
        	update = 1;
		}
		if (update == 1)
		{
			if (run_cl(env, rt, screen) == ERROR)
			{
				printf("Rendering error\n");
				break ;
			}
			SDL_UpdateWindowSurface(window);
			update = 0;
		}
	}
}

void		render(t_env *env, t_rt *rt)
{
	SDL_Window		*window;
	SDL_Surface		*screen;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rt->canvas.width, rt->canvas.height,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	if ((screen = SDL_GetWindowSurface(window)) == NULL)
	{
		printf("Screen could not be created! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	loop(env, rt, window, screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
