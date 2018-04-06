/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 17:20:59 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "types.h"
# include "objects.h"

typedef struct		s_env {
	int				width;
	int				height;
	t_color			background;
	t_obj_lst		*objects;
	t_vec			cam_ang;
	t_vec			cam_orig;
	t_float			fov;
}					t_env;

#endif
