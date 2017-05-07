/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:14:20 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/07 16:29:26 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "includes/libft.h"

char	*ft_ftoa(float nb, int precision)
{
	char	*str;
	char	*entier;
	char	*decimal;
	int		i;

	i = 0;
	entier = ft_itoa((int)nb);
	nb -= (int)nb;
	if (nb < 0)
		nb *= -1;
	if (!(decimal = (char *)malloc(sizeof(char) * (precision + 2))))
		return (NULL);
	decimal[i] = '.';
	while (i < precision)
	{
		nb *= 10;
		decimal[1 + i++] = (int)nb + 48;
		nb -= (int)nb;
	}
	decimal[1 + i] = '\0';
	str = ft_strjoin(entier, decimal);
	ft_strdel(&entier);
	ft_strdel(&decimal);
	return (str);
}
