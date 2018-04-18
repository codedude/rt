/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:36:29 by vparis            #+#    #+#             */
/*   Updated: 2018/04/18 14:51:24 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "opencl.h"

static t_src_def	*opencl_get_source_files(void)
{
	static t_src_def	sources[] = {
		{"kernel/srcs/primary_rays.cl", "primary_rays"},
		{"kernel/srcs/intersect.cl", "intersect"},
		{NULL, NULL}
	};

	return (sources);
}

static int			opencl_init2(t_opencl *env, t_rt *rt)
{
	if (opencl_update_buffers(env, rt) == ERROR)
	{
		ft_putstr("Error : can't write opencl buffers\n");
		return (ERROR);
	}
	if (opencl_kernel_set(env, rt) == ERROR)
	{
		ft_putstr("Error : can't init opencl kernels\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int					opencl_init(t_opencl *env, t_rt *rt)
{
	ft_putstr("Starting to load OpenCL...\n");
	if (opencl_init_device(env) == ERROR)
		return (ERROR);
	if (opencl_init_context(env) == ERROR)
		return (ERROR);
	if (opencl_init_program(env, opencl_get_source_files()) == ERROR)
		return (ERROR);
	if (opencl_init_kernels(env, opencl_get_source_files()) == ERROR)
		return (ERROR);
	if (opencl_init_buffers(env, rt) == ERROR)
	{
		ft_putstr("Error : can't init opencl buffers\n");
		return (ERROR);
	}
	if (opencl_init2(env, rt) == ERROR)
		return (ERROR);
	ft_putstr("OpenCL loaded successfully !\n");
	return (SUCCESS);
}

int					opencl_destroy(t_opencl *ocl)
{
	int		i;

	clReleaseMemObject(ocl->buffers.canvas);
	clReleaseMemObject(ocl->buffers.camera);
	clReleaseMemObject(ocl->buffers.objects);
	clReleaseMemObject(ocl->buffers.screen);
	clReleaseMemObject(ocl->buffers.rays);
	clReleaseMemObject(ocl->buffers.inters);
	clReleaseCommandQueue(ocl->cmd_queue);
	clReleaseContext(ocl->context);
	clReleaseProgram(ocl->program);
	i = 0;
	while (i < KERNEL_NUMBERS)
	{
		clReleaseKernel(ocl->kernels[i]);
		i++;
	}
	return (SUCCESS);
}
