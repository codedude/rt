/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:30:15 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 18:14:43 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rt.h"

# define T_MIN	1e-6

enum {
	CANVAS, CAMERA,
	PLANE, SPHERE, CONE, CYLINDER, DISK, HALF_SPHERE, HYPERBOLOID, TORUS,
	PARABOLOID, PARALLELOGRAM, CUBE, PYRAMID,
	LIGHT_AMBIENT, LIGHT_POINT, LIGHT_SPOT, LIGHT_PAR
};

# define PHONGS			4
# define PHONG_SHINI	0
# define PHONG_KA		1
# define PHONG_KD		2
# define PHONG_KS		3

typedef struct			s_object {
	t_id				id;
	t_int				type;
	t_vec				pos;
	t_vec				dir;
	t_vec				color;
	t_vec				intensity;
	t_float				radius;
	t_float				radius2;
	t_float				phong[PHONGS];
	t_float				reflexion;
	t_float				transparency;
	t_float				refraction;
	t_float				perturbation;
	t_float				angle;
	t_float				size;
}						t_object;

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

__kernel void		primary_rays(__constant t_canvas *canvas,
						__constant t_camera *camera, __global t_ray *rays);
void				raster_to_ndc(__float2 *v, float width, float height);
void				ndc_to_cam_coord(__float2 v, t_vec *vec, float fov,
						float aspect_ratio);
void				pixel_to_ray_in_world(__constant t_camera *camera,
						__constant t_canvas *canvas, t_ray *ray,
						float x, float y);

__kernel void		intersect(__constant t_object *obj, __constant t_ray *rays,
						__global t_inter *inter, int n);

#endif
