/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:31:18 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:13:12 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *s2;

	s2 = (unsigned char*)s;
	while (n--)
	{
		if (*s2 != (unsigned char)c)
			s2++;
		else
			return (s2);
	}
	return (NULL);
}
