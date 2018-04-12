/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:29:36 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 19:55:50 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <OpenCL/OpenCL.h>
#include <assert.h>
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

	if (opencl_kernel_set(&env->opencl, rt) == ERROR)
		return (ERROR);
	global_work_size = rt->canvas.size;
	buffer_size = sizeof(t_ray) * global_work_size;
	err = clEnqueueNDRangeKernel(env->opencl.cmd_queue, env->opencl.kernels[0],
							1, NULL, &global_work_size, NULL, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		printf("err rays\n");
		return (ERROR);
	}
	err = clEnqueueNDRangeKernel(env->opencl.cmd_queue, env->opencl.kernels[1],
							1, NULL, &global_work_size, NULL, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		switch (err) {
			case CL_INVALID_WORK_ITEM_SIZE:
				printf("args\n"); break ;
			case CL_OUT_OF_RESOURCES:
				printf("dim\n"); break ;
			case CL_MEM_OBJECT_ALLOCATION_FAILURE :
				printf("workgroup\n"); break ;
			default:
				break ;
		}
		printf("err intersect\n");
		return (ERROR);
	}
	clFinish(env->opencl.cmd_queue);
	err = clEnqueueReadBuffer(env->opencl.cmd_queue, env->opencl.buffers.screen,
		CL_TRUE, 0, sizeof(t_uint) * rt->canvas.size, (t_uint *)screen->pixels,
		0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		printf("err read back\n");	
		switch (err) {
			case CL_INVALID_MEM_OBJECT:
				printf("mem\n"); break ;
			case CL_INVALID_VALUE:
				printf("value\n"); break ;
			case CL_MEM_OBJECT_ALLOCATION_FAILURE :
				printf("alloc\n"); break ;
			default:
				break ;
		}
		return (ERROR);
	}
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
				cam_pos.s[0] += 1.0;
			else if (event.key.keysym.sym == SDLK_LEFT)
				cam_pos.s[0] -= 1.0;
        	else if (event.key.keysym.sym == SDLK_UP)
				cam_pos.s[1] += 1.0;
        	else if (event.key.keysym.sym == SDLK_DOWN)
				cam_pos.s[1] -= 1.0;
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
	t_uint			*image;

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
	image = (t_uint *)screen->pixels;
	if ((image = (t_uint *)malloc(sizeof(t_uint) * rt->canvas.size)) == NULL)
		return ;
	loop(env, rt, window, screen);
	free(image);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
