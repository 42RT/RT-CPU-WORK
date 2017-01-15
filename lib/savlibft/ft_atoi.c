/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 12:33:51 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/10 15:14:29 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		signe;
	int		c;

	c = 0;
	signe = 1;
	while (ft_isascii(*str) && !ft_isalnum(*str) && *str != '-' && *str != '+')
		str++;
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	if (*str == '+' && *(str - 1) != '-')
		str++;
	while (ft_isdigit(*str))
	{
		c = c + *str - '0';
		if (ft_isdigit(*(str + 1)))
			c = c * 10;
		str++;
	}
	c = c * signe;
	return (c);
}
