/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:36:29 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 17:30:48 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "types.h"
#include "opencl.h"

static int		get_srcs_size(t_src_def *sources)
{
	int	i;

	i = 0;
	while (sources[i].file != NULL)
		i++;
	return (i);
}

static int		format_srcs(t_src_def *sources, char ***srcs)
{
	int		n;
	int		i;

	n = get_srcs_size(sources);
	if ((*srcs = (char **)malloc((n + 1) * sizeof(char *))) == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		if (((*srcs)[i] = ft_strdup(sources[i].file)) == NULL)
		{
			free(*srcs);
			return (0);
		}
		i++;
	}
	(*srcs)[i] = NULL;
	return (n);
}

static void		print_kernel_error(t_opencl *env, cl_int err)
{
	size_t	len;
	char	logs[65000];

	ft_putstr("Error : Failed to build program executable!\n");
	ft_putstr("Error ID : ");
	ft_putnbr((int)err);
	ft_putstr("\nLogs size : ");
	clGetProgramBuildInfo(env->program, env->device, CL_PROGRAM_BUILD_LOG,
							65000, logs, &len);
	ft_putnbr((int)len);
	ft_putstr("\n\n");
	ft_putendl(logs);
	exit(EXIT_FAILURE);
}

int				opencl_init_program(t_opencl *env, t_src_def *sources)
{
	cl_int		err;
	char		**program_srcs;
	int			count;

	if ((count = format_srcs(sources, &program_srcs)) == 0)
		return (ERROR);
	env->program = clCreateProgramWithSource(env->context, (cl_uint)count,
		(const char **)program_srcs, NULL, &err);
	assert(err == CL_SUCCESS);
	ft_strsplit_free(program_srcs);
	err = clBuildProgram(env->program, 0, NULL, KERNEL_INCLUDES,
		NULL, NULL);
	if (err != CL_SUCCESS)
		print_kernel_error(env, err);
	return (SUCCESS);
}

int				opencl_init_kernels(t_opencl *env, t_src_def *sources)
{
	cl_int		err;
	int			i;

	i = 0;
	while (sources[i].file != NULL)
	{
		env->kernels[i] = clCreateKernel(env->program, sources[i].kernel,
			&err);
		assert(err == CL_SUCCESS);
		i++;
	}
	return (SUCCESS);
}
