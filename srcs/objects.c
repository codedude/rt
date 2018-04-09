/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:46:39 by vparis            #+#    #+#             */
/*   Updated: 2018/04/09 18:28:21 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "objects.h"

t_object	*object_new(int type)
{
	t_object	*tmp;

	if ((tmp = (t_object *)malloc(sizeof(t_object))) == NULL)
		return (NULL);
	ft_bzero(tmp, sizeof(t_object));
	tmp->type = type;
	tmp->id = gen_id();
	return (tmp);
}

int			object_add(t_objects *objects, t_object *object)
{
	t_obj_lst	*tmp;

	if ((tmp = (t_obj_lst *)malloc(sizeof(t_obj_lst))) == NULL)
		return (ERROR);
	tmp->object = object;
	tmp->next = objects->objects_lst;
	objects->objects_lst = tmp;
	objects->size += 1;
	return (SUCCESS);
}

void		object_free(t_objects *objects)
{
	t_obj_lst	*iter;
	t_obj_lst	*tmp;

	iter = objects->objects_lst;
	while (iter != NULL)
	{
		tmp = iter->next;
		free(iter);
		iter = tmp;
	}
	objects->objects_lst = NULL;
	objects->size = 0;
	if (objects->objects_array != NULL)
	{
		free(objects->objects_array);
		objects->objects_array = NULL;
	}
}
