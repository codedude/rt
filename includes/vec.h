/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:53:53 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 17:38:15 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H

# include "types.h"

void			vec_norm(t_vec v1);
t_float			vec_dot(t_vec v1, t_vec v2);
t_float			vec_len(t_vec v1);
t_vec		vec3_add(t_vec a, t_vec b):
t_vec		from_to(t_vec from, t_vec to);
t_vec		scaling(t_vec vec, float a);
t_vec		vec3_sub(t_vec a, t_vec b);
t_vec		vec3_opposite(t_vec a);
t_vec		vec3_normalize(t_vec v);

#endif
