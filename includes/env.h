/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/04/17 14:52:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "types.h"
# include "objects.h"
# include "rt.h"
# include "opencl.h"
# include "sdl_m.h"

typedef struct		s_env {
	t_opencl		opencl;
	t_sdl			sdl;
	t_rt			rt;
}					t_env;

int					env_init(t_env *env, char *filename);
void				env_destroy(t_env *env);

#endif
