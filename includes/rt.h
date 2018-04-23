/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/04/18 14:18:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define DEPTH	5
# define REFRACTION_INDEX 1.0f
# define RGB(r, g, b) (256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))
# define BACKGROUND RGB(77, 167, 238)
# define COLOR_MAX 16777215

# include "types.h"
# include "objects.h"
# include <limits.h>

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
	int				canvas_update;
	int				camera_update;
}					t_rt;

int					rt_init(t_rt *rt, char *filename);
int					rt_destroy(t_rt *rt);

int					camera_set_origin(t_rt *rt, t_vec v);
int					camera_set_angle(t_rt *rt, t_vec v);
int					camera_set_fov(t_rt *rt, t_float fov);
t_vec				camera_get_origin(t_rt *rt);
t_vec				camera_get_angle(t_rt *rt);
t_float				camera_get_fov(t_rt *rt);

int					canvas_set_width(t_rt *rt, int width);
int					canvas_set_height(t_rt *rt, int height);
int					canvas_set_bg_color(t_rt *rt, t_color color);
int					canvas_get_width(t_rt *rt);
int					canvas_get_height(t_rt *rt);
t_color				canvas_get_bg_color(t_rt *rt);

#endif
