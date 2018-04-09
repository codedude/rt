/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:58:26 by valentin          #+#    #+#             */
/*   Updated: 2018/04/09 18:43:39 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "types.h"
# include "rt.h"

int		canvas_set_width(t_canvas *canvas, int width)
{
	if (width < 64 || width > 4096)
		return (ERROR);
	canvas->width = width;
	return (SUCCESS);
}

int		canvas_set_height(t_canvas *canvas, int height)
{
	if (height < 64 || height > 2160)
		return (ERROR);
	canvas->height = height;
	return (SUCCESS);
}

int		canvas_set_bg_color(t_canvas *canvas, t_color color)
{
	canvas->bg_color = color;
	return (SUCCESS);
}
