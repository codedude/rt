/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:01:46 by vparis            #+#    #+#             */
/*   Updated: 2018/04/09 19:25:36 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <OpenCL/OpenCL.h>

typedef unsigned long	t_id;
typedef int				t_color;

typedef cl_float		t_float;
typedef cl_double		t_double;
typedef cl_float4		t_vec;
typedef cl_double4		t_vec_d;

/*
** types.c
*/

t_id					gen_id(void);
t_color					rgb_to_color(int r, int g, int b);

/*
** ft_atof_s.c
*/

int						ft_atof_s(char *str, t_float *n);

#endif
