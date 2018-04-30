/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_m.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 11:31:41 by valentin          #+#    #+#             */
/*   Updated: 2018/04/30 11:34:10 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTK_M_H
# define GTK_M_H

typedef struct		s_gtk {
	GtkWindow		*window;
	GtkWidget		*render;
	void			*render_win;
	void			*render_id;
}					t_gtk;

int					gtk_init_m(t_gtk *gtk);
int					gtk_destroy(t_gtk *gtk);
#endif
