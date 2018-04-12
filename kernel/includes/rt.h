/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:30:15 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 17:13:01 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rt.h"

typedef struct		s_inter {
	t_float			t;
	t_int			id;
	t_vec			point;
	t_vec			normal;
}					t_inter;

typedef struct		s_ray {
	t_vec			origin;
	t_vec			dir;
	t_float			refraction;
}					t_ray;

typedef struct		s_canvas {
	t_int			width;
	t_int			height;
	t_int			size;
	t_color			bg_color;
}					t_canvas;

typedef struct		s_camera {
	t_vec			origin;
	t_vec			angle;
	t_float			fov;
}					t_camera;

__kernel void	render_kernel(__global t_ray *rays, __constant t_cam *cam)
__kernel void	intersect(__constant t_object *obj, __constant t_ray *rays,
							__global t_inter *inter, int n);

#endif
