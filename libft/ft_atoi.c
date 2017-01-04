/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 12:48:39 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:05:48 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	i;
	unsigned int	result;
	int				sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] &&
			(str[i] == ' ' || str[i] == '\f' ||
			str[i] == '\r' || str[i] == '\t' ||
			str[i] == '\v' || str[i] == '\n'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' && (sign = -1))
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		result *= 10;
		result += (str[i] - 48);
		i++;
	}
	return (sign * result);
}
