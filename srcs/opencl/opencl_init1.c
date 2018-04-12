/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:36:29 by vparis            #+#    #+#             */
/*   Updated: 2018/04/11 19:07:14 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "types.h"
#include "opencl.h"

static void		print_infos(cl_char vendor_name[1024],
							cl_char device_name[1024])
{
	ft_putstr("\tConnecting to ");
	ft_putstr((char *)vendor_name);
	ft_putstr(" ");
	ft_putstr((char *)device_name);
	ft_putstr("...\n");
}

int				opencl_init_device(t_opencl *env)
{
	cl_int		err;
	cl_char		vendor_name[1024];
	cl_char		device_name[1024];
	size_t		returned_size;

#pragma mark Device Information
	{
		err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &env->cpu, NULL);
		assert(err == CL_SUCCESS);
		err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &env->device, NULL);
		if (err != CL_SUCCESS)
			env->device = env->cpu;
		assert(env->device);
		ft_bzero(vendor_name, sizeof(cl_char) * 1024);
		ft_bzero(device_name, sizeof(cl_char) * 1024);
		err = clGetDeviceInfo(env->device, CL_DEVICE_VENDOR,
							sizeof(vendor_name), vendor_name, &returned_size);
		err |= clGetDeviceInfo(env->device, CL_DEVICE_NAME, sizeof(device_name),
							device_name, &returned_size);
		assert(err == CL_SUCCESS);
		print_infos(vendor_name, device_name);
	}
	return (SUCCESS);
}

int				opencl_init_context(t_opencl *env)
{
	cl_int		err;

#pragma mark Context and Command queue initialisation
	{
		env->context = clCreateContext(0, 1, &env->device, NULL, NULL, &err);
		assert(err == CL_SUCCESS);
		env->cmd_queue = clCreateCommandQueue(env->context, env->device,
											0, NULL);
	}
	return (SUCCESS);
}
