/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:24:48 by vparis            #+#    #+#             */
/*   Updated: 2018/04/08 20:10:51 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "objects.h"
#include "libft.h"
#include "rt.h"

t_parse_objects	*get_parse_objects(void)
{
	static t_parse_objects	parse_objects[] = {
		ADD_OBJECT(canvas, 1), ADD_OBJECT(camera, 1),
		ADD_OBJECT(light_ambient, 1), ADD_OBJECT(light_point, 0),
		ADD_OBJECT(light_spot, 0), ADD_OBJECT(light_par, 0),
		ADD_OBJECT(plane, 0), ADD_OBJECT(sphere, 0),
		ADD_OBJECT(cone, 0), ADD_OBJECT(cylinder, 0),
		ADD_OBJECT(disk, 0), ADD_OBJECT(half_sphere, 0),
		ADD_OBJECT(hyperboloid, 0), ADD_OBJECT(torus, 0),
		ADD_OBJECT(paraboloid, 0), ADD_OBJECT(parallelogram, 0),
		ADD_OBJECT(cube, 0), ADD_OBJECT(pyramid, 0),
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
			return (parse_objects[i].id);
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
