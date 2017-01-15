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

static int		ft_itoa_size(int n)
{
	int		size;

	size = 0;
	while (n)
	{
		++size;
		n /= 10;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	int		size;
	int		zero;
	int		min;
	char	*result;

	size = (n < 0);
	min = (n == -2147483648);
	n += min;
	n = ((n < 0) ? -n : n);
	size += ft_itoa_size(n);
	zero = (size == 0);
	result = (char *)malloc((size + 1 + zero) * sizeof(char));
	*(result) = 0x30 - (3 * (n != 0));
	*(result + size-- + zero) = '\0';
	*(result + size + zero) = n % 10 + 0x30 + min;
	n /= 10;
	while (n)
	{
		--size;
		*(result + size) = n % 10 + 0x30;
		n /= 10;
	}
	return (result);
}
