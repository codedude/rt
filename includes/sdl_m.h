/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_m.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:24:09 by vparis            #+#    #+#             */
/*   Updated: 2018/04/30 16:31:12 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_M_H
# define SDL_M_H

# include <stdlib.h>
# include "SDL.h"
# include "types.h"

typedef struct		s_sdl {
	t_uint			*image;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	size_t			size_line;
	size_t			size_buffer;
	SDL_Window		*window;
}					t_sdl;

/*
** sdl.c
*/

int					sdl_init(t_sdl *sdl, int width, int height);
int					sdl_destroy(t_sdl *sdl);
int					sdl_render(t_sdl *sdl);

#endif
