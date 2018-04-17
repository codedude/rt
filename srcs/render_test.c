/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:29:36 by vparis            #+#    #+#             */
/*   Updated: 2018/04/17 14:55:22 by vparis           ###   ########.fr       */
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

int			run_cl(t_env *env)
{
	cl_int	err;
	size_t	global_work_size;
	size_t	buffer_size;
	cl_ulong time_start;
	cl_ulong time_end;
	cl_event event;
	double nanoSeconds;

	global_work_size = env->rt.canvas.size;
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
		CL_TRUE, 0,
		env->sdl.size_line * env->rt.canvas.height, (void *)env->sdl.image,
		0, NULL, NULL);

	sdl_update(&env->sdl);

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
			cam_pos = camera_get_origin(&env->rt.camera);
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
			camera_set_origin(&env->rt.camera, cam_pos);
			opencl_update_camera(&env->opencl, &env->rt);
        	update = 1;
		}
		if (update == 1 || 1)
		{
			if (run_cl(env) == ERROR)
			{
				printf("Rendering error\n");
				break ;
			}
			sdl_render(&env->sdl);
			get_fps(1, 1);
			update = 0;
		}
	}
}
