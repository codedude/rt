/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:53:53 by vparis            #+#    #+#             */
/*   Updated: 2018/04/23 19:11:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H

# include "types.h"

void			vec_norm(t_vec v1);
t_float			vec_dot(t_vec v1, t_vec v2);
t_float			vec_len(t_vec v1);
t_vec			vec_scalar(t_vec v1, t_float n);
void			vec_opposite(t_vec v2);

#endif
