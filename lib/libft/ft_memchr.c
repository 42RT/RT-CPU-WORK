/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:47:26 by jrouilly          #+#    #+#             */
/*   Updated: 2013/11/26 14:40:48 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*s1;
	unsigned char	c2;

	c2 = (unsigned char)c;
	s1 = (char *)s;
	while (n)
	{
		if (*s1 == c2)
		{
			return (s1);
		}
		--n;
		++s1;
	}
	return (NULL);
}
