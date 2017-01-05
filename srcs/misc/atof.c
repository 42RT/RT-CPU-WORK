/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:52:49 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/26 13:19:35 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_atof_ext(char *str, int i, double a, int sign)
{
	int		j;

	j = 0;
	if (str[i] == '.')
	{
		++i;
		while (ft_isdigit(str[i + j]))
			++j;
		if (sign == 0)
			a = a + (double)ft_atoi(str + i) / pow(10, j);
		else
			a = a - (double)ft_atoi(str + i) / pow(10, j);
	}
	return (a);
}

double	ft_atof(char *str)
{
	double	a;
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	a = 0.0;
	while (!ft_isdigit(str[i]) && str[i] != '-')
		++i;
	if (str[i] == '-')
		sign = 1;
	a = (double)ft_atoi(str + i);
	while (str[i] != '.' && (ft_isdigit(str[i]) || str[i] == ' ' ||
				str[i] == '-'))
		++i;
	a = ft_atof_ext(str, i, a, sign);
	return (a);
}
