/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 12:33:03 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/03 18:19:26 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!*s2)
		return ((char*)s1);
	while (s1[j] && j < n)
	{
		if (s1[j] == s2[i])
			while (s1[j + i] == s2[i] && i + j < n)
			{
				i++;
				if (!s2[i])
					return ((char*)s1 + j);
			}
		i = 0;
		j++;
	}
	return (NULL);
}
