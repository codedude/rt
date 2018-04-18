/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:08:11 by vparis            #+#    #+#             */
/*   Updated: 2018/04/18 16:29:56 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <OpenCL/OpenCL.h>
#include <assert.h>
#include "libft.h"
#include "env.h"
#include "sdl_m.h"
#include "rt.h"
#include "objects.h"
#include "opencl.h"

int			opencl_run_program(t_opencl *ocl, t_rt *rt, t_sdl *sdl)
{
	cl_int		err;
	size_t		global_work_size[2];
	cl_ulong	time_start;
	cl_ulong	time_end;
	cl_event	event;
	double		nanoSeconds;

	global_work_size[0] = rt->canvas.height;
	global_work_size[1] = rt->canvas.width;
	err = clEnqueueNDRangeKernel(ocl->cmd_queue, ocl->kernels[0],
							2, NULL, global_work_size, NULL, 0, NULL, &event);
	
	clWaitForEvents(1, &event);
	clFinish(ocl->cmd_queue);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);

	nanoSeconds = time_end-time_start;
printf("Rays Execution time is: %0.3f milliseconds \n",nanoSeconds / 1000000.0);

	if (err != CL_SUCCESS)
	{
		printf("err rays\n");
		return (ERROR);
	}
	err = clEnqueueNDRangeKernel(ocl->cmd_queue, ocl->kernels[1],
							2, NULL, global_work_size, NULL, 0, NULL, &event);
	clWaitForEvents(1, &event);
	clFinish(ocl->cmd_queue);
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
	if (opencl_get_image(ocl, sdl) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
