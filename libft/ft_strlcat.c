/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:27:10 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:18:43 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dst2;
	const char	*src2;
	size_t		n;
	size_t		len;

	dst2 = dst;
	src2 = src;
	n = size;
	while (n-- != 0 && *dst2 != '\0')
		dst2++;
	len = dst2 - dst;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(src2));
	while (*src2 != '\0')
	{
		if (n != 1)
		{
			*dst2++ = *src2;
			n--;
		}
		src2++;
	}
	*dst2 = '\0';
	return (len + (src2 - src));
}
