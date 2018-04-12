/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:37:23 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 18:11:17 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_H
# define OPENCL_H

# include <OpenCL/OpenCL.h>
# include "types.h"
# include "rt.h"

# define KERNEL_NUMBERS		2
# define KERNEL_INCLUDES	"-I kernel/includes -I /usr/include"

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

int						opencl_init(t_opencl *env);
int						opencl_destroy(t_opencl *ocl);

int						opencl_init_device(t_opencl *env);
int						opencl_init_context(t_opencl *env);
int						opencl_init_program(t_opencl *env, t_src_def *sources);
int						opencl_init_kernels(t_opencl *env, t_src_def *sources);

int						opencl_init_buffers(t_opencl *ocl, t_rt *rt);
int						opencl_update_canvas(t_opencl *ocl, t_rt *rt);
int						opencl_update_camera(t_opencl *ocl, t_rt *rt);
int						opencl_update_objects(t_opencl *ocl, t_rt *rt);

int						opencl_kernel_set(t_opencl *ocl, t_rt *rt);

#endif
