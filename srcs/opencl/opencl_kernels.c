/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:12:47 by vparis            #+#    #+#             */
/*   Updated: 2018/04/18 14:57:51 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "opencl.h"
#include "rt.h"

int		opencl_kernel_set_object(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	err  = clSetKernelArg(ocl->kernels[1],  0, sizeof(cl_mem),
		&ocl->buffers.objects);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[1],  3, sizeof(t_int),
		&rt->objects.size);
	if (err != CL_SUCCESS)
		return (ERROR);

		err  = clSetKernelArg(ocl->kernels[2],  0, sizeof(cl_mem),
		&ocl->buffers.objects);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[2],  4, sizeof(t_int),
		&rt->objects.size);
	if (err != CL_SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int		opencl_kernel_set(t_opencl *ocl, t_rt *rt)
{
	cl_int	err;

	err  = clSetKernelArg(ocl->kernels[0],  0, sizeof(cl_mem),
		&ocl->buffers.canvas);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[0],  1, sizeof(cl_mem),
		&ocl->buffers.camera);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[0],  2, sizeof(cl_mem),
		&ocl->buffers.rays);
	if (err != CL_SUCCESS)
		return (ERROR);

	err  = clSetKernelArg(ocl->kernels[1],  0, sizeof(cl_mem),
		&ocl->buffers.objects);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[1],  1, sizeof(cl_mem),
		&ocl->buffers.rays);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[1],  2, sizeof(cl_mem),
		&ocl->buffers.inters);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[1],  3, sizeof(t_int),
		&rt->objects.size);
	if (err != CL_SUCCESS)
		return (ERROR);

	err  = clSetKernelArg(ocl->kernels[2],  0, sizeof(cl_mem),
		&ocl->buffers.objects);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[2],  1, sizeof(cl_mem),
		&ocl->buffers.rays);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[2],  2, sizeof(cl_mem),
		&ocl->buffers.inters);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[2],  3, sizeof(cl_mem),
		&ocl->buffers.intensity);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[2],  4, sizeof(t_int),
		&rt->objects.size);
	if (err != CL_SUCCESS)
		return (ERROR);

	err  = clSetKernelArg(ocl->kernels[3],  0, sizeof(cl_mem),
		&ocl->buffers.inters);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[3],  1, sizeof(cl_mem),
		&ocl->buffers.intensity);
	if (err != CL_SUCCESS)
		return (ERROR);
	err  = clSetKernelArg(ocl->kernels[3],  2, sizeof(cl_mem),
		&ocl->buffers.screen);
	if (err != CL_SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
