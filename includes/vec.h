/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:53:53 by vparis            #+#    #+#             */
/*   Updated: 2018/04/27 14:25:36 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H

# include "types.h"

# define VEC_ZERO			(t_vec){0.0, 0.0, 0.0, 0.0}
# define VEC_INIT(a, b, c)	(t_vec){(a), (b), (c), 0.0}
# define MAT_ID	(t_vec[3]){VEC_INIT(1.0, 0.0, 0.0), VEC_INIT(0.0, 1.0, 0.0), VEC_INIT(0.0, 0.0, 1.0)}

t_vec			vec_norm(t_vec v1);
t_float			vec_dot(t_vec v1, t_vec v2);
t_float			vec_len(t_vec v1);
void			vec_print(t_vec v, char *name);

void			matrix_rot_vec(t_vec matrix[3], t_vec v);
t_vec			matrix_mul_vec(t_vec matrix[3], t_vec v);
void			matrix_init_value(void);

void			matrix_mul_matrix(t_vec m1[3], t_vec m2[3], t_vec ret[3]);
void			matrix_rotx(t_vec ret[3], double teta);
void			matrix_roty(t_vec ret[3], double teta);
void			matrix_rotz(t_vec ret[3], double teta);

#endif
