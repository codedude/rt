/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:09:01 by vparis            #+#    #+#             */
/*   Updated: 2018/04/08 22:28:56 by valentin         ###   ########.fr       */
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
		ADD_TYPE(background, 3, "0"),
		ADD_TYPE(ang, 3, "1"), ADD_TYPE(orig, 3, "1"), ADD_TYPE(fov, 1, "1"),
		ADD_TYPE(pos, 3, "2 3 4 5 15 16 17"),
		ADD_TYPE(dir, 3, "2 3 4 5"),
		ADD_TYPE(radius, 1, "2 3 4 5"),
		ADD_TYPE(color, 3, "2 3 4 5"),
		ADD_TYPE(intensity, 3, "14 15 16 17"),
		ADD_TYPE(phong, 4, "2 3 4 5"),
		ADD_TYPE(angle, 1, ""),
		ADD_TYPE(size, 1, ""),
		ADD_TYPE(reflexion, 1, ""),
		ADD_TYPE(refraction, 1, ""),
		ADD_TYPE(transparency, 1, ""),
		ADD_TYPE(perturbation, 1, ""),
		{NULL, NULL, NULL, 0}};

	return (parse_type);
}

static int		check_counter_details_other(int counter[OBJECT_DETAILS_SIZE],
						int type)
{
	if (1)
		return (1);
	return (0);
}

static int		check_counter_details(int counter[OBJECT_DETAILS_SIZE],
						int type)
{
	if (type == canvas)
		return (counter[0] == 1 && counter[1] == 1 && counter[2] == 1);
	else if (type == camera)
		return (counter[3] == 1 && counter[4] == 1 && counter[5] == 1);
	else if (type == light_ambient)
		return (counter[10] == 1);
	else if (type > light_ambient)
		return (counter[6] == 1 && counter[10] == 1);
	return (check_counter_details_other(counter, type));
}

static int		parse_global_need_space(int *i, int type, t_object **obj)
{
	if (type <= camera)
		*obj = NULL;
	else if ((*obj = object_new(type)) == NULL)
		return (ERROR);
	*i = 0;
	return (SUCCESS);
}

int				parse_global(t_env *env, char **str, int type)
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
	return (check_counter_details(counter, type) ? i : -1);
}
