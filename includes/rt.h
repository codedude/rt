/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/04/13 15:58:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "types.h"
# include "objects.h"

/*
**
*/

typedef struct		s_inter {
	t_float			t;
	t_int			id;
	t_color			color;
	t_vec			point;
	t_vec			normal;
}					t_inter;

typedef struct		s_ray {
	t_vec			origin;
	t_vec			dir;
	t_float			refraction;
}					t_ray;

/*
** Canvas : the physical window, can change
*/

typedef struct		s_canvas {
	t_int			width;
	t_int			height;
	t_int			size;
	t_float			ratio[2];
	t_color			bg_color;
}					t_canvas;

/*
** Camera : eye of the scene, movable object
*/

typedef struct		s_camera {
	t_vec			origin;
	t_vec			angle;
	t_float			fov;
}					t_camera;

/*
** Entire environnement for RT
*/

typedef struct		s_rt {
	t_canvas		canvas;
	t_camera		camera;
	t_objects		objects;
}					t_rt;

t_rt				*rt_init(char *filename);
int					rt_destroy(t_rt **rt);

int					camera_set_origin(t_camera *camera, t_vec v);
int					camera_set_angle(t_camera *camera, t_vec v);
int					camera_set_fov(t_camera *camera, t_float fov);
t_vec				camera_get_origin(t_camera *camera);
t_vec				camera_get_angle(t_camera *camera);
t_float				camera_get_fov(t_camera *camera);

int					canvas_set_width(t_canvas *canvas, int width);
int					canvas_set_height(t_canvas *canvas, int height);
int					canvas_set_bg_color(t_canvas *canvas, t_color color);
int					canvas_get_width(t_canvas *canvas);
int					canvas_get_height(t_canvas *canvas);
t_color				canvas_get_bg_color(t_canvas *canvas);

#endif
