/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:30:32 by vparis            #+#    #+#             */
/*   Updated: 2018/05/01 17:37:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "render.h"
#include "bmp.h"

int		manage_binds_mouse(SDL_Event *event, t_env *env, int *update)
{
	(void)env;
	(void)update;
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		printf("%d, %d\n", (int)event->button.x, (int)event->button.y);
	}
	return (1);
}
