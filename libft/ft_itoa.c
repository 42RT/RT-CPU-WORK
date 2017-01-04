/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 21:16:21 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:11:05 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int			itoa_size(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = (unsigned int)n * (-1);
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char				*ft_itoa(int n)
{
	char			sign;
	char			*result;
	int				i;

	i = 0;
	sign = '+';
	result = (char *)malloc(sizeof(char) * (itoa_size(n) + 1));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		sign = '-';
		n = (unsigned int)n * (-1);
	}
	while ((unsigned int)n > 9)
	{
		result[i] = ((unsigned int)n % 10) + 48;
		n = (unsigned int)n / 10;
		i++;
	}
	result[i] = (unsigned int)n + 48;
	((sign == '-') ? result[i + 1] = sign : 0) && i++;
	result[i + 1] = '\0';
	return (ft_strrev(result));
}
