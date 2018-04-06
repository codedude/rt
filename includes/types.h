/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:01:46 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 18:03:59 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <OpenCL/OpenCL.h>

typedef int			t_color;

typedef cl_float	t_float;
typedef cl_double	t_double;
typedef cl_float4	t_vec;
typedef cl_double4	t_vec_d;

/*
** types.c
*/

t_float				clamp_float(t_float f, t_float lmin, t_float lmax);
int					clamp_int(int f, int lmin, int lmax);
t_color				rgb_to_color(int r, int g, int b);

/*
** ft_atof_s.c
*/

int					ft_atof_s(char *str, t_float *n);

#endif
