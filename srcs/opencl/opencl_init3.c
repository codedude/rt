/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:09:05 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 14:35:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "opencl.h"
#include "rt.h"

int		opencl_update_canvas(t_opencl *ocl, t_env *env)
{
	cl_int	err;

	err = clEnqueueWriteBuffer(ocl->cmd_queue, ocl->buffers.canvas, CL_TRUE, 0,
			sizeof(t_canvas), (void *)&env->canvas, 0, NULL, NULL);
	return (err == CL_SUCCESS ? SUCCESS : ERROR);
}

int		opencl_update_camera(t_opencl *ocl, t_env *env)
{
	cl_int	err;

	err = clEnqueueWriteBuffer(ocl->cmd_queue, ocl->buffers.camera, CL_TRUE, 0,
			sizeof(t_camera), (void *)&env->camera, 0, NULL, NULL);
	return (err == CL_SUCCESS ? SUCCESS : ERROR);
}

int		opencl_update_objects(t_opencl *ocl, t_env *env)
{
	cl_int	err;

	if (object_gen_array(&env->objects) == ERROR)
		return (ERROR);
	err = clEnqueueWriteBuffer(ocl->cmd_queue, ocl->buffers.objects, CL_TRUE, 0,
			sizeof(t_object) * env->objects.size, 
			(void *)env->objects.objects_array, 0, NULL, NULL);
	return (err == CL_SUCCESS ? SUCCESS : ERROR);
}

int		opencl_init_buffer(t_opencl *ocl, t_env *env)
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
		CL_MEM_READ_ONLY, sizeof(t_object) * env->objects.size, NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.objects == NULL)
		return (ERROR);
	ocl->buffers.screen = clCreateBuffer(ocl->context,
		CL_MEM_WRITE_ONLY,
		sizeof(cl_int) * (env->canvas.width * env->canvas.height), NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.screen == NULL)
		return (ERROR);
	opencl_update_canvas(ocl, env);
	opencl_update_camera(ocl, env);
	opencl_update_objects(ocl, env);
	clFinish(ocl->cmd_queue);
	return (SUCCESS);
}
