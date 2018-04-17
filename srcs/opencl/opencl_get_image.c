/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_get_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:13:55 by vparis            #+#    #+#             */
/*   Updated: 2018/04/17 15:26:46 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/OpenCL.h>
#include <stdlib.h>
#include <assert.h>
#include "libft.h"
#include "opencl.h"
#include "sdl_m.h"

int		opencl_get_image(t_opencl *ocl, t_sdl *sdl)
{
	cl_int	err;

	err = clEnqueueReadBuffer(ocl->cmd_queue, ocl->buffers.screen,
		CL_TRUE, 0, sdl->size_buffer,
		(void *)sdl->image, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		opencl_err_enqueue("opencl_get_image", err);
		return (ERROR);
	}
	return (SUCCESS);
}
