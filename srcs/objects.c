/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:46:39 by vparis            #+#    #+#             */
/*   Updated: 2018/04/10 14:18:53 by vparis           ###   ########.fr       */
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

int			object_del(t_objects *objects, t_id id)
{
	t_obj_lst	*iter;
	t_obj_lst	*tmp;

	tmp = NULL;
	iter = objects->objects_lst;
	while (iter != NULL && iter->object->id != id)
	{
		tmp = iter;
		iter = iter->next;
	}
	if (iter == NULL)
		return (ERROR);
	if (tmp == NULL)
		objects->objects_lst = iter->next;
	else
		tmp->next = iter->next;
	objects->size -= 1;
	free(iter);
	return (SUCCESS);
}

t_object	*object_get(t_objects *objects, t_id id)
{
	t_obj_lst	*iter;

	iter = objects->objects_lst;
	while (iter != NULL && iter->object->id != id)
		iter = iter->next;
	if (iter == NULL)
		return (NULL);
	return (iter->object);
}

void		object_destroy(t_objects *objects)
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
