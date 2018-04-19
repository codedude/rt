/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:13:55 by vparis            #+#    #+#             */
/*   Updated: 2018/04/17 15:31:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <stdlib.h>
#include <assert.h>
#include "libft.h"

void	opencl_err_enqueue(char *str, cl_int err)
{
	ft_putstr(str);
	ft_putstr(" : ");
	if (err == CL_INVALID_COMMAND_QUEUE)
		ft_putendl("CL_INVALID_COMMAND_QUEUE");
	else if (err == CL_INVALID_CONTEXT)
		ft_putendl("CL_INVALID_CONTEXT");
	else if (err == CL_INVALID_MEM_OBJECT)
		ft_putendl("CL_INVALID_MEM_OBJECT");
	else if (err == CL_INVALID_VALUE)
		ft_putendl("CL_INVALID_VALUE");
	else if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE)
		ft_putendl("CL_MEM_OBJECT_ALLOCATION_FAILURE");
	else if (err == CL_INVALID_PROGRAM)
		ft_putendl("CL_INVALID_PROGRAM");
	else if (err == CL_INVALID_BUILD_OPTIONS)
		ft_putendl("CL_INVALID_BUILD_OPTIONS");
	else if (err == CL_COMPILER_NOT_AVAILABLE)
		ft_putendl("CL_COMPILER_NOT_AVAILABLE");
	else if (err == CL_BUILD_PROGRAM_FAILURE)
		ft_putendl("CL_BUILD_PROGRAM_FAILURE");
	else if (err == CL_INVALID_OPERATION)
		ft_putendl("CL_INVALID_OPERATION");
	else if (err == CL_OUT_OF_RESOURCES)
		ft_putendl("CL_OUT_OF_RESOURCES");
	else if (err == CL_OUT_OF_HOST_MEMORY)
		ft_putendl("CL_OUT_OF_HOST_MEMORY");
	else if (err == CL_INVALID_OPERATION)
		ft_putendl("CL_INVALID_OPERATION");
	else if (err == CL_INVALID_DEVICE)
		ft_putendl("CL_INVALID_DEVICE");

	else if (err == CL_INVALID_PROGRAM_EXECUTABLE)
		ft_putendl("CL_INVALID_PROGRAM_EXECUTABLE");
	else if (err == CL_INVALID_KERNEL)
		ft_putendl("CL_INVALID_KERNEL");
	else if (err == CL_OUT_OF_HOST_MEMORY)
		ft_putendl("CL_OUT_OF_HOST_MEMORY");
	else if (err == CL_INVALID_KERNEL_ARGS)
		ft_putendl("CL_INVALID_KERNEL_ARGS");
	else if (err == CL_INVALID_WORK_DIMENSION)
		ft_putendl("CL_INVALID_WORK_DIMENSION");
	else if (err == CL_OUT_OF_RESOURCES)
		ft_putendl("CL_OUT_OF_RESOURCES");
	else if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE)
		ft_putendl("CL_MEM_OBJECT_ALLOCATION_FAILURE");
	else if (err == CL_INVALID_EVENT_WAIT_LIST)
		ft_putendl("CL_INVALID_EVENT_WAIT_LIST");
	else if (err == CL_OUT_OF_HOST_MEMORY)
		ft_putendl("CL_OUT_OF_HOST_MEMORY");

	else if (err == CL_INVALID_WORK_ITEM_SIZE)
		ft_putendl("CL_INVALID_WORK_ITEM_SIZE");
	else if (err == CL_INVALID_WORK_GROUP_SIZE)
		ft_putendl("CL_INVALID_WORK_GROUP_SIZE");
	else if (err == CL_INVALID_WORK_DIMENSION)
		ft_putendl("CL_INVALID_WORK_DIMENSION");
	else if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE)
		ft_putendl("CL_MEM_OBJECT_ALLOCATION_FAILURE");
	else if (err == CL_INVALID_EVENT_WAIT_LIST)
		ft_putendl("CL_INVALID_EVENT_WAIT_LIST");
	else if (err == CL_OUT_OF_HOST_MEMORY)
		ft_putendl("CL_OUT_OF_HOST_MEMORY");
	else if (err == CL_SUCCESS)
		ft_putendl("CL_SUCCESS");
	else
		ft_putendl("error");
}
