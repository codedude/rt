/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:47:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/09 18:32:53 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include "types.h"

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
	return id;
}
