/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gtk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:40:24 by vparis            #+#    #+#             */
/*   Updated: 2018/04/27 17:50:54 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "render.h"

static GtkWindow *gtk_window;
static GtkWidget *gtk_da;
static void *gdk_window;
static void *window_id;

static gboolean idle(void *ud) {
    (void)ud;
    if(!sdl_window) {
        printf("creating SDL window for window id %p\n", window_id);
        sdl_window = SDL_CreateWindowFrom(window_id);
        printf("sdl_window=%p\n", sdl_window);
        if(!sdl_window) {
            printf("%s\n", SDL_GetError());
        }
        sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
        printf("sdl_renderer=%p\n", sdl_renderer);
        if(!sdl_renderer) {
            printf("%s\n", SDL_GetError());
        }
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
        SDL_RenderClear(sdl_renderer);
        SDL_RenderPresent(sdl_renderer);
    }
    return true;
}

void	loop_gtk{
    gtk_init(&argc, &argv);
    gtk_window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(gtk_window, "test");

    gtk_da = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(gtk_window), gtk_da);
    gtk_widget_show_all(GTK_WIDGET(gtk_window));

    gdk_window = gtk_widget_get_window(GTK_WIDGET(gtk_da));
    window_id = (void*)(intptr_t)GDK_WINDOW_XID(gdk_window);

    SDL_Init(SDL_INIT_VIDEO);

    g_idle_add(&idle, 0);
    gtk_main();
    return 0;
}