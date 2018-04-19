/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init_buffers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:09:05 by vparis            #+#    #+#             */
/*   Updated: 2018/04/18 14:37:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "opencl.h"
#include "rt.h"

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
		sizeof(t_uint) * rt->canvas.size, NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.screen == NULL)
		return (ERROR);

	ocl->buffers.rays = clCreateBuffer(ocl->context,
		CL_MEM_READ_WRITE,
		sizeof(t_ray) * rt->canvas.size, NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.rays == NULL)
		return (ERROR);

	ocl->buffers.inters = clCreateBuffer(ocl->context,
		CL_MEM_READ_WRITE,
		sizeof(t_inter) * rt->canvas.size, NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.inters == NULL)
		return (ERROR);

	ocl->buffers.intensity = clCreateBuffer(ocl->context,
		CL_MEM_READ_WRITE,
		sizeof(t_vec) * rt->canvas.size, NULL, &err);
	if (err != CL_SUCCESS || ocl->buffers.intensity == NULL)
		return (ERROR);

	return (SUCCESS);
}
