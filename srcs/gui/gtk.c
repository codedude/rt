/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 11:29:31 by valentin          #+#    #+#             */
/*   Updated: 2018/04/30 11:48:39 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <gtk/gtk.h>
//#include <gdk/gdkx.h>
#include "libft.h"
#include "gtk_m.h"

int			gtk_init_m(t_gtk *gtk)
{
	gtk_init(NULL, NULL);
    if ((gtk->window = (GtkWindow *)gtk_window_new(GTK_WINDOW_TOPLEVEL))
    	== NULL)
    	return (ERROR);
    gtk_window_set_title(gtk->window, "RT");

    gtk->render = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(gtk->window), gtk->render);
    gtk_widget_show_all(GTK_WIDGET(gtk->window));

    gtk->render_win = gdk_quartz_window_get_nsview(
        gtk_widget_get_window((gtk->render)));
    //gtk->render_id = (void*)(intptr_t)GDK_WINDOW_XID(gtk->render_win);
	return (SUCCESS);
}

int			gtk_destroy(t_gtk *gtk)
{
	return (SUCCESS);
}
