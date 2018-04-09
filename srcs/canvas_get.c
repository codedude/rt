/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:29:16 by valentin          #+#    #+#             */
/*   Updated: 2018/04/09 19:32:10 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "rt.h"

int		canvas_get_width(t_canvas *canvas)
{
	return (canvas->width);
}

int		canvas_get_height(t_canvas *canvas)
{
	return (canvas->height);
}

t_color	canvas_get_bg_color(t_canvas *canvas)
{
	return (canvas->bg_color);
}
