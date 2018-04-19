/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:37:23 by vparis            #+#    #+#             */
/*   Updated: 2018/04/18 23:18:56 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_H
# define OPENCL_H

# include <OpenCL/OpenCL.h>
# include "types.h"
# include "rt.h"
# include "sdl_m.h"

# define KERNEL_NUMBERS		4
# define KERNEL_INCLUDES	"-I kernel/includes"

typedef struct			s_src_def {
	const char			*file;
	const char			*kernel;
}						t_src_def;

typedef struct			s_opencl_buffer {
	cl_mem				canvas;
	cl_mem				camera;
	cl_mem				objects;
	cl_mem				screen;
	cl_mem				rays;
	cl_mem				inters;
	cl_mem 				intensity;
}						t_opencl_buffer;

typedef struct			s_opencl {
	cl_context			context;
	cl_device_id		cpu;
	cl_device_id		device;
	cl_program			program;
	cl_kernel			kernels[KERNEL_NUMBERS];
	cl_command_queue	cmd_queue;
	t_opencl_buffer		buffers;
}						t_opencl;

/*
** opencl.c
*/

int						opencl_init(t_opencl *env, t_rt *rt);
int						opencl_destroy(t_opencl *ocl);

/*
** opencl_init1.c
*/

int						opencl_init_device(t_opencl *env);
int						opencl_init_context(t_opencl *env);

/*
** opencl_init2.c
*/

int						opencl_init_program(t_opencl *env, t_src_def *sources);
int						opencl_init_kernels(t_opencl *env, t_src_def *sources);

/*
** opencl_init_buffers.c
*/

int						opencl_init_buffers(t_opencl *ocl, t_rt *rt);

/*
** opencl_update_buffers.c
*/

int						opencl_update_buffers(t_opencl *ocl, t_rt *rt);

/*
** opencl_kernels.c
*/

int						opencl_kernel_set(t_opencl *ocl, t_rt *rt);
int						opencl_kernel_set_object(t_opencl *ocl, t_rt *rt);

/*
** opencl_get_image.c
*/

int						opencl_get_image(t_opencl *ocl, t_sdl *sdl);

/*
** opencl_errors.c
*/

void					opencl_err_enqueue(char *str, cl_int err);

/*
** opencl_run.c
*/

int						opencl_run_program(t_opencl *ocl, t_rt *rt, t_sdl *sdl);
#endif
