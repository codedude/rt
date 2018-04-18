/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_update_buffers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:30:59 by vparis            #+#    #+#             */
/*   Updated: 2018/04/18 14:57:01 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "opencl.h"
#include "rt.h"

static int	opencl_update_canvas(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	if (rt->canvas_update == 0)
		return (SUCCESS);
	rt->canvas_update = 0;
	err = clEnqueueWriteBuffer(ocl->cmd_queue, ocl->buffers.canvas, CL_TRUE, 0,
			sizeof(t_canvas), (void *)&rt->canvas, 0, NULL, NULL);
	return (err == CL_SUCCESS ? SUCCESS : ERROR);
}

static int	opencl_update_camera(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	if (rt->camera_update == 0)
		return (SUCCESS);
	rt->camera_update = 0;
	err = clEnqueueWriteBuffer(ocl->cmd_queue, ocl->buffers.camera, CL_TRUE, 0,
			sizeof(t_camera), (void *)&rt->camera, 0, NULL, NULL);
	return (err == CL_SUCCESS ? SUCCESS : ERROR);
}

static int	opencl_update_objects_buffer(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	clReleaseMemObject(ocl->buffers.objects);
	ocl->buffers.objects = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY, sizeof(t_object) * rt->objects.size, NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.objects == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	opencl_update_objects(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	if (rt->objects.is_update == 0)
		return (SUCCESS);
	rt->objects.is_update = 0;
	if (rt->objects.last_size != rt->objects.size)
	{
		if (opencl_update_objects_buffer(ocl, rt) == ERROR)
			return (ERROR);
		if (opencl_kernel_set_object(ocl, rt) == ERROR)
			return (ERROR);
	}
	if (objects_gen_array(&rt->objects) == ERROR)
		return (ERROR);
	err = clEnqueueWriteBuffer(ocl->cmd_queue, ocl->buffers.objects, CL_TRUE, 0,
			sizeof(t_object) * rt->objects.size,
			(void *)rt->objects.objects_array, 0, NULL, NULL);
	return (err == CL_SUCCESS ? SUCCESS : ERROR);
}

int			opencl_update_buffers(t_opencl *ocl, t_rt *rt)
{
	if (opencl_update_canvas(ocl, rt) == ERROR)
		return (ERROR);
	if (opencl_update_camera(ocl, rt) == ERROR)
		return (ERROR);
	if (opencl_update_objects(ocl, rt) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
