/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:03:26 by vparis            #+#    #+#             */
/*   Updated: 2018/04/23 19:06:18 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"
# include "env.h"

# define FLOAT_ZERO		0.0f
# define FLOAT_MAX		1e6f
# define FLOAT_MIN		1e-5f
# define BIAIS			1e-5f
# define MAX_DEPTH		4

typedef struct		s_algo {
	t_env			*env;
	int				start;
	int				end;
}					t_algo;

typedef struct		s_inter {
	t_float			t;
	t_object		*obj;
	t_vec			color;
	t_vec			point;
	t_vec			point_biais;
	t_vec			normal;
}					t_inter;

typedef struct		s_ray {
	t_vec			origin;
	t_vec			dir;
	t_float			refraction;
}					t_ray;


void				render_compute(t_env *env);
int					render_update(t_env *env);
int					rt(void *data);

/*
** inter
*/
int					trace(t_rt *rt, t_ray *ray, t_inter *inter,
						t_float max_inter);
void				compute_hit_normal(t_ray *ray, t_inter *inter);
void				compute_hit_biais(t_inter *inter);

t_float				solve_quadra(t_float abc[3], t_float *t);

t_float				intersect_sphere(t_ray *ray, t_object *obj, t_float *t);
void				norm_sphere(t_ray *ray_hit, t_object *obj, t_inter *inter);

t_float				intersect_plane(t_ray *ray, t_object *obj, t_float *t);
void				norm_plane(t_ray *ray, t_object *obj, t_inter *inter);


t_uint		compute_color(t_ray ray, int depth, t_rt *rt);
t_uint		transmitted_light(t_ray ray, t_inter inter, int depth, t_rt *rt, t_color local);
t_uint		color_intensity(t_vec intensity, t_vec color);
t_uint		calc_color(t_float i, t_uint color);

/*
** Compute light intensity
*/

t_vec		light(t_inter it, t_vec v, t_rt *rt);
t_float		diffuse_light(t_ray *r, t_inter it, int *j, t_rt *rt);
t_vec		light_specular(t_inter it, t_vec i[4], t_vec v, t_ray *r);
t_uint		reflect(t_ray ray, t_rt *rt, int depth, t_inter inter);
t_ray		reflected_ray(t_inter inter, t_vec ray);
t_uint		refract(t_ray ray, t_rt *rt, int depth, t_inter inter);
t_ray		refract_ray(t_ray ray, t_inter inter);
t_float		fresnel(t_ray ray, t_inter inter);


/*
** Compute intersections
*/

int				closest_intersect(t_ray ray, 
		t_float t_max, t_objects objects, t_inter *inter);
t_float		inters(t_ray ray, t_object *obj);
t_float		r_inter_plan(t_ray ray, t_object *plan);
t_float		r_inter_sphere(t_ray ray, t_object *obj);

/*
** Compute shape's normal
*/

t_vec		point_normal(t_object *obj, t_vec intersection, t_ray ray);
t_vec		point_ray_intersect(double t, t_ray ray);
t_vec		sphere_normal(t_vec center, t_vec point);
t_vec		cyl_normal(t_vec bottom, t_vec top, t_vec point);
t_vec		cone_normal(t_object cone, t_vec point);


#endif