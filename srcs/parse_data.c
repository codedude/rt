/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:24:48 by vparis            #+#    #+#             */
/*   Updated: 2018/04/07 18:26:38 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "rt.h"

t_parse_objects	*get_parse_objects(void)
{
	static t_parse_objects	parse_objects[] = {
		{"canvas", 0, 1},
		{"camera", 1, 1},
		{"plane", 2, 0},
		{"sphere", 3, 0},
		{"cone", 4, 0},
		{"cylinder", 5, 0},
		{"disk", 6, 0},
		{"half_sphere", 7, 0},
		{"hyperboloid", 8, 0},
		{"torus", 9, 0},
		{"paraboloid", 10, 0},
		{"parallelogram", 11, 0},
		{"cube", 12, 0},
		{"pyramid", 13, 0},
		{"light_ambient", 14, 1},
		{"light_point", 15, 0},
		{"light_spot", 16, 0},
		{"light_par", 17, 0},
		{NULL, 0, 0}};

	return (parse_objects);
}

static int		parse_check_header(char *str)
{
	int				i;
	t_parse_objects	*parse_objects;

	parse_objects = get_parse_objects();
	i = 0;
	while (parse_objects[i].name != NULL)
	{
		if (ft_strcmp(str, parse_objects[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int		check_counter_objects(int counter[OBJECT_SIZE])
{
	int				i;
	t_parse_objects	*parse_objects;

	parse_objects = get_parse_objects();
	i = 0;
	while (parse_objects[i].name != NULL)
	{
		if (parse_objects[i].required > 0)
		{
			if (counter[parse_objects[i].id] != parse_objects[i].required)
				return (0);
		}
		i++;
	}
	return (1);
}

static int		parse_data_2(t_env *env, char **data, int *i, int type)
{
	int	n_type;

	if ((n_type = parse_global(env, &data[*i], type)) > 0)
	{
		*i += n_type;
		if (data[*i] != NULL && (data[*i][0] != T_CLOSE || data[*i][1] != 0))
			return (ERROR);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int				parse_data(t_env *env, char **data)
{
	int		i;
	int		type;
	int		r;
	int		counter[OBJECT_SIZE];

	i = 0;
	ft_bzero(counter, OBJECT_SIZE * sizeof(int));
	while (data[i] != NULL)
	{
		r = ERROR;
		if ((type = parse_check_header(data[i])) == -1)
			break ;
		counter[type] += 1;
		if (data[++i] != NULL && (data[i][0] != T_OPEN || data[i][1] != 0))
			break ;
		i++;
		if (parse_data_2(env, data, &i, type) == ERROR)
			break ;
		i++;
		r = SUCCESS;
	}
	return (r == ERROR || !check_counter_objects(counter) ? ERROR : SUCCESS);
}
