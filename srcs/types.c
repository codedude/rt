/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:47:21 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 18:02:18 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_float		clamp_float(t_float f, t_float lmin, t_float lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}

int			clamp_int(int f, int lmin, int lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}

t_color		rgb_to_color(int r, int g, int b)
{
	t_color	c;

	c = 0;
	c |= (b & 0xFF);
	c |= (g & 0xFF) << 8;
	c |= (r & 0xFF) << 16;
	return (c);
}
