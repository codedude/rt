/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/04/30 18:34:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "types.h"
# include "objects.h"
# include "rt.h"
# include "ft_tpool.h"
# include "sdl_m.h"

# define THREADS		4
# define TASKS			32

typedef struct		s_env {
	t_tpool			*tp;
	t_sdl			sdl;
	t_rt			rt;
	int				show_fps;
	int				save_img;
}					t_env;

int					env_init(t_env *env, char *filename);
void				env_destroy(t_env *env);


int					manage_binds(SDL_Event *event, t_env *env, int *update);

#endif
