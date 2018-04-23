/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:03:26 by vparis            #+#    #+#             */
/*   Updated: 2018/04/20 17:18:25 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct	s_algo {
	t_env		*env;
	int			start;
	int			end;
}				t_algo;


typedef struct		s_inter {
	t_float			t;
	t_int			id;
	t_vec			point;
	t_vec			normal;
}					t_inter;

typedef struct		s_ray {
	t_vec			origin;
	t_vec			dir;
	t_float			ref_index;
}					t_ray;


void		render_compute(t_env *env);
int			render_update(t_env *env);

int			rt(void *data);
t_ray		compute_primary_rays(int x, int y, t_canvas canvas, t_camera camera);
t_uint		compute_color(t_ray ray, int depth, t_rt *rt);
void		ft_put_pixel(int x, int y, t_uint color, t_rt *rt);

t_uint		color_intensity(t_vec intensity, t_vec color);
t_uint		calc_color(t_float i, t_uint color);

/*
** Compute light intensity
*/

t_vec		light(t_inter it, t_vec v, t_rt *rt);
t_float		diffuse_light(t_ray *r, t_inter it, int *j, t_rt *rt);
t_vec		light_specular(t_inter it, t_float i[4], t_vec v, t_ray *r);
t_uint		reflect(t_ray ray, t_rt *rt, int depth, t_inter inter);
t_ray		reflected_ray(t_inter inter, t_vec ray);
t_uint		refract(t_ray ray, t_env *env, int depth, t_inter inter);
t_ray		refract_ray(t_ray ray, t_inter inter);
t_float		fresnel(t_ray ray, t_inter inter);


/*
** Compute intersections
*/

t_inter		closest_intersect(t_ray ray, t_float t_min,
		t_float t_max, t_objects *objects);
t_float		inters(t_ray ray, t_object obj);
t_float		r_inter_plan(t_ray ray, t_object plan);
t_float		r_inter_sphere(t_ray ray, t_object obj);

/*
** Compute shape's normal
*/

t_vec		point_normal(t_object obj, t_vec intersection, t_ray ray);
t_vec		point_ray_intersect(double t, t_ray ray);
t_vec		sphere_normal(t_vec center, t_vec point);
t_vec		cyl_normal(t_vec bottom, t_vec top, t_vec point);
t_vec		cone_normal(t_cone c, t_vec point);


#endif
