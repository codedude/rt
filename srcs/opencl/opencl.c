/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:36:29 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 14:31:13 by vparis           ###   ########.fr       */
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
		{"kernel/srcs/rt.cl", "rt"},
		{NULL, NULL}
	};

	return (sources);
}

int					opencl_init(t_opencl *env)
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
	ft_putstr("OpenCL loaded successfully !\n");
	return (SUCCESS);
}

int					opencl_destroy(t_opencl *env)
{
	int		i;

	clReleaseCommandQueue(env->cmd_queue);
	clReleaseContext(env->context);
	clReleaseProgram(env->program);
	i = 0;
	while (i < KERNEL_NUMBERS)
	{
		clReleaseKernel(env->kernels[i]);
		i++;
	}
	return (SUCCESS);
}
