/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:09:01 by vparis            #+#    #+#             */
/*   Updated: 2018/04/24 18:23:18 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"
#include "rt.h"
#include "objects.h"

t_parse_type	*get_parse_funs(void)
{
	static t_parse_type	parse_type[] = {
		ADD_TYPE(width, 1, "0"), ADD_TYPE(height, 1, "0"),
		ADD_TYPE(background, 3, "0"), ADD_TYPE(fov, 1, "1"),
		ADD_TYPE(ang, 3, "1"), ADD_TYPE(origin, 3, "1"),
		ADD_TYPE(pos, 3, "2 3 4 5 15 16"),
		ADD_TYPE(dir, 3, "2 3 4 5 17"),
		ADD_TYPE(radius, 1, "2 3 4 5"),
		ADD_TYPE(color, 3, "2 3 4 5"),
		ADD_TYPE(intensity, 3, "14 15 16 17"),
		ADD_TYPE(phong, 3, "2 3 4 5"),
		ADD_TYPE(angle, 1, ""),
		ADD_TYPE(size, 1, ""),
		ADD_TYPE(reflexion, 1, ""),
		ADD_TYPE(refraction, 1, ""),
		ADD_TYPE(transparency, 1, ""),
		ADD_TYPE(perturbation, 1, ""),
		{NULL, NULL, NULL, 0}};

	return (parse_type);
}

static int		check_counter_details(int counter[OBJECT_DETAILS_SIZE],
									int type)
{
	int				i;
	int				n;
	t_parse_type	*types;

	i = 0;
	n = 0;
	types = get_parse_funs();
	while (types[i].name != NULL)
	{
		if (check_line_object(types[i].types, type) == SUCCESS)
		{
			if (counter[i] != 1)
				return (ERROR);
			n += 1;
		}
		i++;
	}
	return (n == 0 ? ERROR : SUCCESS);
}

static int		parse_global_need_space(int *i, int type, t_object **obj)
{
	if (type == CANVAS || type == CAMERA)
		*obj = NULL;
	else if ((*obj = object_new(type)) == NULL)
		return (ERROR);
	*i = 0;
	return (SUCCESS);
}

int				parse_global(t_rt *env, char **str, int type)
{
	int				i;
	int				r;
	t_object		*obj;
	char			**tmp;
	int				counter[OBJECT_DETAILS_SIZE];

	ft_bzero(counter, OBJECT_DETAILS_SIZE * sizeof(int));
	if (parse_global_need_space(&i, type, &obj) == ERROR)
		return (-1);
	while (*(str + i) != NULL)
	{
		if ((tmp = check_line(*(str + i), type, &r)) == NULL)
			break ;
		if (counter[r] == 1 || parse_details(env, r, tmp[1], obj) == ERROR)
		{
			ft_strsplit_free(tmp);
			return (-1);
		}
		counter[r] += 1;
		ft_strsplit_free(tmp);
		i++;
	}
	if (obj != NULL)
		object_add(&(env->objects), obj);
	return (check_counter_details(counter, type) == SUCCESS ? i : -1);
}
