/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/04/10 15:24:44 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "types.h"
# include "objects.h"

/*
** Canvas : the physical window, can change
*/

typedef struct		s_canvas {
	int				width;
	int				height;
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

typedef struct		s_env {
	t_canvas		canvas;
	t_camera		camera;
	t_objects		objects;
}					t_env;

t_env				*env_init(char *filename);
int					env_destroy(t_env **env);

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
