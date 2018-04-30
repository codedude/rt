/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:32:54 by vparis            #+#    #+#             */
/*   Updated: 2018/04/30 14:03:18 by vparis           ###   ########.fr       */
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

enum {
	NONE, MARBLE, WOOD
};

# define PHONGS			3
# define PHONG_SHINI	0
# define PHONG_KD		1
# define PHONG_KS		2

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
	t_int				perturbation;
	t_float				angle;
	t_float				size;
	t_vec				obj_to_w[3];
	t_vec				w_to_obj[3];
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
	int					is_update;
	int					last_size;
}						t_objects;

/*
** objects.c
*/

void					objects_init(t_objects *objects);
void					objects_destroy(t_objects *objects);
int						objects_gen_array(t_objects *objects);

/*
** objects_queue.c
*/

t_object				*object_new(int type);
int						object_add(t_objects *objects, t_object *object);
int						object_del(t_objects *objects, t_id id);
t_object				*object_get(t_objects *objects, t_id id);

/*
** objects_format.c
*/

int						object_is_light(t_object *object);
t_obj_lst				*objects_get_iter(t_objects *objects);

/*
** object_setX.c
*/

int						object_set_pos(t_object *obj, t_vec pos);
int						object_set_dir(t_object *obj, t_vec dir);
int						object_set_color(t_object *obj, t_vec color);
int						object_set_intensity(t_object *obj, t_vec intensity);
int						object_set_radius(t_object *obj, t_float radius);
int						object_set_phong(t_object *obj, t_float phong[PHONGS]);
int						object_set_reflexion(t_object *obj, t_float n);
int						object_set_transparency(t_object *obj, t_float n);
int						object_set_refraction(t_object *obj, t_float n);
int						object_set_perturbation(t_object *obj, int n);
int						object_set_angle(t_object *obj, t_float n);
int						object_set_size(t_object *obj, t_float n);
int						object_set_matrix(t_object *obj, t_vec rot);
int						object_set_inverse_matrix(t_object *obj, t_vec rot);

#endif
