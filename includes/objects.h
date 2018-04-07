/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:32:54 by vparis            #+#    #+#             */
/*   Updated: 2018/04/07 18:23:47 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "types.h"

# define OBJECTS		16

/*
** canvas = 0, camera = 1 => always firsts
** plane = 2... => in between
** light_ambient = 14.. => always the lasts
*/

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

/*
** type : int of object
** id : int unique id (incremental 0..)
** radius2 : radius * radius cache
** other : from parsing
** int * 2 + vec * 4 + float * 12 = 4 + 16 + 48 = 68o/object
** 1 object = 68o, 100 objects = 6Ko, 1000 objects = 66Ko
*/

typedef struct			s_object {
	int					type;
	int					id;
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

typedef struct			s_obj_lst {
	struct s_obj_lst	*next;
	t_object			*object;
}						t_obj_lst;

t_object				*object_new(int type);
t_obj_lst				*object_add(t_obj_lst **objects, t_object *object);
void					object_free(t_obj_lst **objects);

void					object_set_pos(t_object *obj, t_vec pos);
void					object_set_dir(t_object *obj, t_vec dir);
void					object_set_intensity(t_object *obj, t_vec intensity);
void					object_set_color(t_object *obj, t_vec color);
void					object_set_radius(t_object *obj, t_float radius);
void					object_set_phong(t_object *obj, t_float phong[PHONGS]);

#endif
