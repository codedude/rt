/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_keydown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:31:59 by vparis            #+#    #+#             */
/*   Updated: 2018/05/01 19:33:47 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "vec.h"
#include "rt.h"
#include "objects.h"
#include "render.h"
#include "bmp.h"

int		manage_binds_down(t_env *env, int *update, const Uint8 *state)
{
	t_vec		cam_pos;
	t_vec		cam_ang;
	int			smth_changed;

	smth_changed = 1;
	cam_pos = camera_get_origin(&env->rt);
	cam_ang = camera_get_angle(&env->rt);
	if (state[SDL_SCANCODE_Q])
		cam_ang[0] += 1.0;
	if (state[SDL_SCANCODE_A])
		cam_ang[0] -= 1.0;
	if (state[SDL_SCANCODE_W])
		cam_ang[1] += 1.0;
	if (state[SDL_SCANCODE_S])
		cam_ang[1] -= 1.0;
	if (state[SDL_SCANCODE_E])
		cam_ang[2] += 1.0;
	if (state[SDL_SCANCODE_D])
		cam_ang[2] -= 1.0;
	if (state[SDL_SCANCODE_RIGHT])
		cam_pos += matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(1.0, 0.0, 0.0));
	if (state[SDL_SCANCODE_LEFT])
		cam_pos += matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(-1.0, 0.0, 0.0));
	if (state[SDL_SCANCODE_UP])
		cam_pos += matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(0.0, 1.0, 0.0));
	if (state[SDL_SCANCODE_DOWN])
		cam_pos += matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(0.0, -1.0, 0.0));
	if (state[SDL_SCANCODE_Z])
		cam_pos += matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(0.0, 0.0, -1.0));
	if (state[SDL_SCANCODE_X])
		cam_pos += matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(0.0, 0.0, 1.0));
	smth_changed = 1;
	if (smth_changed == 1)
	{
		camera_set_origin(&env->rt, cam_pos);
		camera_set_angle(&env->rt, cam_ang);
		*update = 1;
	}
	return (1);
}
