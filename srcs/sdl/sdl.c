/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:23:03 by vparis            #+#    #+#             */
/*   Updated: 2018/04/17 15:32:42 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"

static int		sdl_init2(t_sdl *sdl, int width, int height)
{
	if ((sdl->window = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN)) == NULL)
	{
		ft_putstr("Window could not be created ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	if ((sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		ft_putstr("Renderer could not be created ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	if ((sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_BGRA32,
		SDL_TEXTUREACCESS_STATIC, width, height)) == NULL)
	{
		ft_putstr("Texture could not be created ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	return (SUCCESS);
}

int				sdl_init(t_sdl *sdl, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_putstr("SDL could not initialize ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	sdl->size_line = width * sizeof(t_uint);
	sdl->size_buffer = height * sdl->size_line;
	if (sdl_init2(sdl, width, height) == ERROR)
		return (ERROR);
	if ((sdl->image = (t_uint *)malloc(sdl->size_buffer)) == NULL)
	{
		ft_putendl("Image buffer cannot be created !");
		return (ERROR);
	}
	return (SUCCESS);
}

int				sdl_destroy(t_sdl *sdl)
{
	if (sdl->image != NULL)
	{
		free(sdl->image);
		sdl->image = NULL;
	}
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	return (SUCCESS);
}

int				sdl_render(t_sdl *sdl)
{
	SDL_UpdateTexture(sdl->texture, NULL, (void *)sdl->image, sdl->size_line);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
	return (SUCCESS);
}
