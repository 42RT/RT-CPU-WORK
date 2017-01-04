/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 18:45:55 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:13:00 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	c2;
	unsigned char	*src2;
	unsigned char	*dest2;

	i = 0;
	c2 = (unsigned char)c;
	dest2 = (unsigned char*)dest;
	src2 = (unsigned char *)src;
	while (i < n && src2[i] != c2)
	{
		dest2[i] = src2[i];
		i++;
	}
	if (i == n)
		return (NULL);
	if (src2[i] == c2)
	{
		dest2[i] = src2[i];
		i++;
	}
	return ((void*)(dest2 + i));
}
