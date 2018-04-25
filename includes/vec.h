/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:53:53 by vparis            #+#    #+#             */
/*   Updated: 2018/04/25 02:53:46 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H

# include "types.h"

# define VEC_INIT	(t_vec){0.0, 0.0, 0.0}
t_vec			vec_norm(t_vec v1);
t_float			vec_dot(t_vec v1, t_vec v2);
t_float			vec_len(t_vec v1);
t_vec			vec_scalar(t_vec v1, t_float n);
t_vec			vec_opposite(t_vec v2);
void			vec_print(t_vec v, char *name);

#endif
