/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:02:53 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/15 15:53:29 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	result;
	int		size;
	int		i;
	int		j;

	result = ft_strlen(dst) + ft_strlen(src);
	result = (result < dstsize ? result : dstsize + ft_strlen(src));
	i = 0;
	j = ft_strlen(dst);
	size = (int)dstsize;
	size -= (ft_strlen(dst) + 1);
	if (size > 0)
	{
		while ((size > 0) && *(src + i))
		{
			*(dst + j + i) = *(src + i);
			++i;
			--size;
		}
		*(dst + j + i) = '\0';
	}
	return (result);
}
