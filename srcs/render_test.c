/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:29:36 by vparis            #+#    #+#             */
/*   Updated: 2018/04/13 16:22:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
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

void	get_fps(int show_fps, int refresh)
{
	static struct timeval	last = {0, 0};
	double					fps;
	struct timeval			new;

	if (show_fps == 0)
		return ;
	gettimeofday(&new, NULL);
	if (refresh == 1)
	{
		fps = (new.tv_sec - last.tv_sec) * 1000 + (new.tv_usec - last.tv_usec)
			/ 1000.;
		ft_putstr("FPS : ");
		ft_putnbr((int)(1000. / fps));
		ft_putchar('\n');
	}
	last.tv_usec = new.tv_usec;
	last.tv_sec = new.tv_sec;
}

int			run_cl(t_env *env, t_rt *rt, SDL_Renderer *renderer,
	SDL_Texture *texture, t_uint *image)
{
	cl_int	err;
	size_t	global_work_size;
	size_t	buffer_size;
	cl_ulong time_start;
	cl_ulong time_end;
	cl_event event;
	double nanoSeconds;

	global_work_size = rt->canvas.size;
	buffer_size = sizeof(t_ray) * global_work_size;
	err = clEnqueueNDRangeKernel(env->opencl.cmd_queue, env->opencl.kernels[0],
							1, NULL, &global_work_size, NULL, 0, NULL, &event);
	
	clWaitForEvents(1, &event);
	clFinish(env->opencl.cmd_queue);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

	nanoSeconds = time_end-time_start;
printf("Rays Execution time is: %0.3f milliseconds \n",nanoSeconds / 1000000.0);

	if (err != CL_SUCCESS)
	{
		printf("err rays\n");
		return (ERROR);
	}
	err = clEnqueueNDRangeKernel(env->opencl.cmd_queue, env->opencl.kernels[1],
							1, NULL, &global_work_size, NULL, 0, NULL, &event);
	clWaitForEvents(1, &event);
	clFinish(env->opencl.cmd_queue);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

	nanoSeconds = time_end-time_start;
printf("Inter Execution time is: %0.3f milliseconds \n\n",nanoSeconds / 1000000.0);

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
	err = clEnqueueReadBuffer(env->opencl.cmd_queue, env->opencl.buffers.screen,
		CL_TRUE, 0, sizeof(t_uint) * rt->canvas.size, (void *)image,
		0, NULL, NULL);

	SDL_UpdateTexture(texture, NULL, (void *)image,
		rt->canvas.width * sizeof(t_uint));
    SDL_RenderCopy(renderer, texture, NULL, NULL);

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

void		loop(t_env *env, t_rt *rt, SDL_Renderer *renderer,
	SDL_Texture *texture, t_uint *image)
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
		if (update == 1 || 1)
		{
			if (run_cl(env, rt, renderer, texture, image) == ERROR)
			{
				printf("Rendering error\n");
				break ;
			}
			SDL_RenderPresent(renderer);
			//get_fps(1, 1);
			update = 0;
		}
	}
}

void		render(t_env *env, t_rt *rt)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	t_uint			*image;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	window = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rt->canvas.width, rt->canvas.height,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	if ((renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED)) == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n",
			SDL_GetError());
		return ;
	}
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32,
        SDL_TEXTUREACCESS_STREAMING | SDL_RENDERER_PRESENTVSYNC,
        rt->canvas.width, rt->canvas.height);
	if ((image = (t_uint *)malloc(sizeof(t_uint) * rt->canvas.size)) == NULL)
		return ;
	loop(env, rt, renderer, texture, image);
	free(image);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
