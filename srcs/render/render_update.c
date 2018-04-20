/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:16:18 by vparis            #+#    #+#             */
/*   Updated: 2018/04/20 17:20:41 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "objects.h"
#include "env.h"

int		render_update(t_env *env)
{
	if (objects_gen_array(&(env->rt.objects)) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
