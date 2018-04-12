/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:09:05 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 15:19:17 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "opencl.h"
#include "rt.h"

int			opencl_update_canvas(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	err = clEnqueueWriteBuffer(ocl->cmd_queue, ocl->buffers.canvas, CL_TRUE, 0,
			sizeof(t_canvas), (void *)&rt->canvas, 0, NULL, NULL);
	return (err == CL_SUCCESS ? SUCCESS : ERROR);
}

int			opencl_update_camera(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

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

int			opencl_update_objects(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	if (rt->objects.is_update == 0)
		return (SUCCESS);
	rt->objects.is_update = 0;
	if (rt->objects.last_size != rt->objects.size)
	{
		if (opencl_update_objects_buffer(ocl, rt) == ERROR)
			return (ERROR);
	}
	if (objects_gen_array(&rt->objects) == ERROR)
		return (ERROR);
	err = clEnqueueWriteBuffer(ocl->cmd_queue, ocl->buffers.objects, CL_TRUE, 0,
			sizeof(t_object) * rt->objects.size,
			(void *)rt->objects.objects_array, 0, NULL, NULL);
	return (err == CL_SUCCESS ? SUCCESS : ERROR);
}

int			opencl_init_buffers(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	ocl->buffers.camera = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY, sizeof(t_camera), NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.camera == NULL)
		return (ERROR);
	ocl->buffers.canvas = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY, sizeof(t_canvas), NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.canvas == NULL)
		return (ERROR);
	ocl->buffers.objects = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY, sizeof(t_object) * rt->objects.size, NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.objects == NULL)
		return (ERROR);
	ocl->buffers.screen = clCreateBuffer(ocl->context,
		CL_MEM_WRITE_ONLY,
		sizeof(cl_int) * (rt->canvas.width * rt->canvas.height), NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.screen == NULL)
		return (ERROR);
	opencl_update_canvas(ocl, rt);
	opencl_update_camera(ocl, rt);
	opencl_update_objects(ocl, rt);
	clFinish(ocl->cmd_queue);
	return (SUCCESS);
}
