/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:09:01 by vparis            #+#    #+#             */
/*   Updated: 2018/04/07 18:36:41 by vparis           ###   ########.fr       */
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
		{"width", &parse_t_width, "0", 1},
		{"height", &parse_t_height, "0", 1},
		{"background", &parse_t_background, "0", 3},
		{"ang", &parse_t_ang, "1", 3},
		{"orig", &parse_t_orig, "1", 3},
		{"fov", &parse_t_fov, "1", 1},
		{"pos", &parse_t_pos, "2 3 4 5 15 16 17", 3},
		{"dir", &parse_t_dir, "2 3 4 5", 3},
		{"radius", &parse_t_radius, "2 3 4 5", 1},
		{"color", &parse_t_color, "2 3 4 5", 3},
		{"intensity", &parse_t_intensity, "14 15 16 17", 3},
		{"phong", &parse_t_phong, "2 3 4 5", 4},
		{"angle", &parse_t_angle, "", 1},
		{"size", &parse_t_size, "", 1},
		{"reflexion", &parse_t_reflexion, "", 1},
		{"refraction", &parse_t_refraction, "", 1},
		{"transparency", &parse_t_transparency, "", 1},
		{"perturbation", &parse_t_perturbation, "", 1},
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
	if (type == CANVAS)
		return (counter[0] == 1 && counter[1] == 1 && counter[2] == 1);
	else if (type == CAMERA)
		return (counter[3] == 1 && counter[4] == 1 && counter[5] == 1);
	else if (type == LIGHT_AMBIENT)
		return (counter[10] == 1);
	else if (type > LIGHT_AMBIENT)
		return (counter[6] == 1 && counter[10] == 1);
	return (check_counter_details_other(counter, type));
}

static int		parse_global_need_space(int *i, int type, t_object **obj)
{
	if (type <= CAMERA)
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
