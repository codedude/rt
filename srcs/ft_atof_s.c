/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:02:28 by vparis            #+#    #+#             */
/*   Updated: 2018/04/06 18:03:33 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "ft_math.h"

static int	ft_atof64_s_divi(size_t len)
{
	int	divi;

	divi = 1;
	while (len--)
		divi *= 10;
	return (divi);
}

static void	compute_d(int d[2], char *str, t_float *n, int sign)
{
	int	divi;

	divi = ft_atof64_s_divi(ft_strlen(str));
	if (sign < 0)
		*n = (t_float)d[0] - (t_float)d[1] / (t_float)divi;
	else
		*n = (t_float)d[0] + (t_float)d[1] / (t_float)divi;
}

int			ft_atof_s(char *str, t_float *n)
{
	char	**parts;
	int		d[2];
	int		sign;

	if ((parts = ft_strsplit(str, '.')) == NULL)
		return (ERROR);
	if (parts[1] == NULL)
	{
		ft_strsplit_free(parts);
		return (ERROR);
	}
	sign = (parts[0][0] == '-') ? -1 : 1;
	if (ft_atoi_s(parts[0], &d[0]) == ERROR
		|| ft_atoi_s(parts[1], &d[1]) == ERROR)
	{
		*n = 0.0;
		ft_strsplit_free(parts);
		return (ERROR);
	}
	else
		compute_d(d, parts[1], n, sign);
	ft_strsplit_free(parts);
	return (SUCCESS);
}
