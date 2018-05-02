/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:52:10 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 12:33:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"
# include "env.h"

# define FLOAT_ZERO			0.0
# define FLOAT_MAX			1e6
# define FLOAT_MIN			1e-5
# define BIAIS				1e-6
# define MAX_DEPTH			4
# define REFRACTION_DEFAULT	1.0

typedef struct		s_algo {
	t_env			*env;
	int				start;
	int				end;
}					t_algo;

typedef struct		s_inter {
	t_float			t;
	t_object		*obj;
	t_vec			point;
	t_vec			obj_coord;
	t_vec			point_biais;
	t_vec			normal;
}					t_inter;

typedef struct		s_ray {
	t_vec			origin;
	t_vec			dir;
	t_float			refraction;
}					t_ray;

typedef struct		s_hit {
	t_ray			ray;
	t_inter			inter;
}					t_hit;

void				render_compute(t_env *env);
int					render_update(t_env *env);
int					rt(void *data);
t_object			*get_hit_object(t_rt *rt, int x, int y);
void				compute_primary_ray(int x, int y, t_rt *rt, t_ray *ray);

/*
** inter
*/

int					trace(t_rt *rt, t_hit *hit, t_float max_inter);
void				compute_hit_normal(t_ray *ray, t_inter *inter);
void				compute_hit_biais(t_inter *inter);

t_float				solve_quadra(t_float abc[3], t_object *obj);

t_float				intersect_sphere(t_ray *ray, t_object *obj, t_float *t);
void				norm_sphere(t_ray *ray_hit, t_object *obj, t_inter *inter);

t_float				intersect_plane(t_ray *ray, t_object *obj, t_float *t);
void				norm_plane(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_cone(t_ray *ray, t_object *obj, t_float *t);
void				norm_cone(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_cylinder(t_ray *ray, t_object *obj, t_float *t);
void				norm_cylinder(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_paraboloid(t_ray *ray, t_object *obj, t_float *t);
void				norm_paraboloid(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_hyperboloid(t_ray *ray, t_object *obj,
						t_float *t);
void				norm_hyperboloid(t_ray *ray, t_object *obj, t_inter *inter);

t_float				intersect_cube(t_ray *ray, t_object *obj, t_float *t);
void				norm_cube(t_ray *ray, t_object *obj, t_inter *inter);

t_vec				compute_color(t_rt *rt, t_hit *hit, int depth);

int					is_cut(t_object obj, t_hit *hit, t_float t, t_ray simple);

/*
** Light effect : reflexion and refraction
*/

t_ray				reflected_ray(t_inter inter, t_vec ray);
t_vec				reflexion(t_rt *rt, t_hit *hit, int depth);

t_vec				refract(t_rt *rt, t_hit *hit, int depth);
t_ray				refract_ray(t_ray ray, t_inter inter);
t_float				fresnel(t_ray ray, t_inter inter);

/*
** Compute light intensity
*/

t_vec				light(t_inter it, t_vec v, t_rt *rt);
t_float				diffuse_light(t_ray *r, t_inter it, int *j, t_rt *rt);
t_vec				light_specular(t_inter it, t_vec i[4], t_vec v, t_ray *r);

t_vec				color_perturbation(t_inter inter);
double				noise3(double vec[3]);
t_vec				marble1(t_float t, t_inter inter);
t_vec				marble2(t_float t, t_inter inter);
t_vec				normal_perturbation(t_inter	inter);
t_vec				chess(t_inter inter);

#endif
