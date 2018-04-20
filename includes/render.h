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


void			render_compute(t_env *env);
int				render_update(t_env *env);

int				rt(void *data);
t_ray			compute_primary_rays(int x, int y, t_canvas canvas, t_camera camera);
t_uint			compute_color(t_ray ray, int depth, t_rt *rt);
ft_put_pixel(int x, int y, t_uint color, t_rt *rt);

#endif
