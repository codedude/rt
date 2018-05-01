/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_keydown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:31:59 by vparis            #+#    #+#             */
/*   Updated: 2018/05/01 17:38:12 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "render.h"
#include "bmp.h"

int		manage_binds_down(t_env *env, int *update, const Uint8 *state)
{
	t_vec		cam_pos;
	int			smth_changed;

	smth_changed = 1;
	cam_pos = camera_get_origin(&env->rt);
	if (state[SDL_SCANCODE_RIGHT])
		cam_pos[0] += 1.0;
	if (state[SDL_SCANCODE_LEFT])
		cam_pos[0] -= 1.0;
	if (state[SDL_SCANCODE_UP])
		cam_pos[1] += 1.0;
	if (state[SDL_SCANCODE_DOWN])
		cam_pos[1] -= 1.0;
	if (state[SDL_SCANCODE_Z])
		cam_pos[2] -= 1.0;
	if (state[SDL_SCANCODE_X])
		cam_pos[2] += 1.0;
	smth_changed = 1;
	if (smth_changed == 1)
	{
		camera_set_origin(&env->rt, cam_pos);
		*update = 1;
	}
	return (1);
}
