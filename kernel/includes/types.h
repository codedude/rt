/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:01:46 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 17:35:49 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# ifndef M_PI
#  define M_PI		(3.141592653589f)
# endif
# define DEG_TO_RAD (M_PI / 180.f)
# define RAD_TO_DEG (180.f / M_PI)

typedef unsigned long	t_id;
typedef int				t_color;

typedef int				t_int;
typedef float			t_float;
typedef double			t_double;
typedef float4			t_vec;
typedef double4			t_vec_d;

#endif
