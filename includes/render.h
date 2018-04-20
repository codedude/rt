/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:03:26 by vparis            #+#    #+#             */
/*   Updated: 2018/04/20 17:18:25 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct	s_algo {
	t_env		*env;
	int			start;
	int			end;
}				t_algo;

void			render_compute(t_env *env);
int				render_update(t_env *env);

int				rt(void *data);

#endif
