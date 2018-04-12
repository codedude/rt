/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:29:36 by vparis            #+#    #+#             */
/*   Updated: 2018/04/12 15:39:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "opencl.h"

void		loop(t_env *env, t_rt *rt, SDL_Window *window,
	SDL_Surface *screen)
{
	int			loop;
	int			update;
	SDL_Event	event;

	loop = 1;
	update = 0;
	while (loop == 1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			loop = 0;
		if (update == 1)
		{
			//run kernel
			SDL_UpdateWindowSurface(window);
			update = 0;
		}
	}
}

void		render(t_env *env, t_rt *rt)
{
	SDL_Window		*window;
	SDL_Surface		*screen;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rt->canvas.width, rt->canvas.height,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	if ((screen = SDL_GetWindowSurface(window)) == NULL)
	{
		printf("Screen could not be created! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	loop(env, rt, window, screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
