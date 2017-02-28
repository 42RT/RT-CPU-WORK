/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:58:32 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/12 15:20:31 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			*ft_hextoa(unsigned int n)
{
	char	*result;
	int		i;

	result = (char *)malloc(9 * sizeof(char));
	*(result) = 0x30 - (3 * (n != 0));
	result[8] = 0;
	result[0] = '0';
	result[1] = '0';
	result[2] = '0';
	result[3] = '0';
	result[4] = '0';
	result[5] = '0';
	result[6] = '0';
	result[7] = '0';
	i = 8;
	while (--i >= 0 && n)
	{
		result[i] = (n % 16 < 10 ? n % 16 : n % 16 + 39) + 0x30;
		n /= 16;
	}
	return (result);
}
