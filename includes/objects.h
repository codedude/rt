/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:32:54 by vparis            #+#    #+#             */
/*   Updated: 2018/04/09 22:11:34 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "types.h"

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
** ulong + int + vec * 4 + float * 12 = 8 + 4 + 64 + 48 = 124o/object
** sizeof => 128o
** 100 objects = 12.5Ko, 1000 objects = 125Ko
*/

typedef struct			s_object {
	t_id				id;
	int					type;
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

/*
** List of all objects
*/

typedef struct			s_obj_lst {
	struct s_obj_lst	*next;
	t_object			*object;
}						t_obj_lst;

/*
** Objects : list of objects
** objects_array : generate light first array to send to GPU, id object = id pos
*/

typedef struct			s_objects {
	t_obj_lst			*objects_lst;
	int					size;
	t_object			*objects_array;
}						t_objects;

t_object				*object_new(int type);
int						object_add(t_objects *objects, t_object *object);
int						object_del(t_objects *objects, t_id id);
t_object				*object_get(t_objects *objects, t_id id);
void					object_free(t_objects *objects);

void					object_set_pos(t_object *obj, t_vec pos);
void					object_set_dir(t_object *obj, t_vec dir);
void					object_set_intensity(t_object *obj, t_vec intensity);
void					object_set_color(t_object *obj, t_vec color);
void					object_set_radius(t_object *obj, t_float radius);
void					object_set_phong(t_object *obj, t_float phong[PHONGS]);

#endif
