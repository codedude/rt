/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:32:54 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 18:11:51 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "types.h"

# define OBJECTS		4
# define PLANE			0
# define SPHERE			1
# define CONE			2
# define CYLINDER		3
# define LIGHT			4

# define PHONGS			4
# define PHONG_SHINI	0
# define PHONG_KA		1
# define PHONG_KD		2
# define PHONG_KS		3

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
	t_float				angle;
	t_float				height;
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
