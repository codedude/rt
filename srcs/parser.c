/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:31:17 by valentin          #+#    #+#             */
/*   Updated: 2018/04/07 18:32:27 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "rt.h"

int			parse_map(t_env *env, char *map)
{
	char	*map_str;
	char	**map_cut;

	if (check_map(map) == ERROR)
	{
		ft_putendl("Invalid file");
		return (ERROR);
	}
	if ((map_str = read_map(map)) == NULL)
		return (ERROR);
	map_cut = cut_map(map_str);
	free(map_str);
	if (map_cut == NULL)
		return (ERROR);
	if (parse_data(env, map_cut) == ERROR)
	{
		ft_putendl("Invalid file");
		ft_strsplit_free(map_cut);
		return (ERROR);
	}
	ft_strsplit_free(map_cut);
	return (SUCCESS);
}
