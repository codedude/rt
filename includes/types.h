/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:01:46 by vparis            #+#    #+#             */
/*   Updated: 2018/04/20 15:42:27 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef unsigned long	t_id;
typedef int				t_color;

typedef int				t_int;
typedef unsigned int	t_uint;
typedef float			t_float;
typedef double			t_double;
typedef t_float			t_vec __attribute__((vector_size(16),aligned(16)));
typedef t_double		t_vec_d __attribute__((vector_size(32),aligned(32)));

/*
** types.c
*/

t_id					gen_id(void);
t_uint					rgb_to_color(int r, int g, int b);
void					get_fps(int show_fps, int refresh);

#endif
