/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:58:23 by hcaillau          #+#    #+#             */
/*   Updated: 2018/02/22 16:02:29 by hcaillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib_vec.h"

VEC3	cross_prod(VEC3 a, VEC3 b)
{
	VEC3	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}
