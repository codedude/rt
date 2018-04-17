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
	else
		ft_putendl("error");
}
