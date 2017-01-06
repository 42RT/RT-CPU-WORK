/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:18:34 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/03 18:15:08 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	if (!*s2)
		return ((char*)s1);
	while (*s1)
	{
		if (*s1 == s2[i])
			while (*(s1 + i) == s2[i])
			{
				i++;
				if (!s2[i])
					return ((char*)s1);
			}
		i = 0;
		s1++;
	}
	return (NULL);
}
