/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:47:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/17 15:29:32 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include "types.h"
#include "libft.h"

t_color		rgb_to_color(int r, int g, int b)
{
	t_color	c;

	c = 0;
	c |= (b & 0xFF);
	c |= (g & 0xFF) << 8;
	c |= (r & 0xFF) << 16;
	return (c);
}

/*
** Takes the array id, return unique ID
*/

t_id		gen_id(void)
{
	struct timeval	t;
	t_id			id;
	t_id			u_id;

	u_id = (t_id)rand();
	gettimeofday(&t, NULL);
	id = ((t.tv_sec * 1000 * 1000) + (t.tv_usec * 1000)) << 42;
	id |= (u_id % 16777216) << 24;
	return (id);
}

void		get_fps(int show_fps, int refresh)
{
	static struct timeval	last = {0, 0};
	double					fps;
	struct timeval			new;

	if (show_fps == 0)
		return ;
	gettimeofday(&new, NULL);
	if (refresh == 1)
	{
		fps = (new.tv_sec - last.tv_sec) * 1000 + (new.tv_usec - last.tv_usec)
			/ 1000.;
		ft_putstr("FPS : ");
		ft_putnbr((int)(1000. / fps));
		ft_putchar('\n');
	}
	last.tv_usec = new.tv_usec;
	last.tv_sec = new.tv_sec;
}
