/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 14:52:17 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:20:30 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s2[i] == '\0')
		return (char *)(s1);
	while (s1[i] != '\0')
	{
		if (s1[i] == s2[j] && i < n)
		{
			while (s2[j] && s1[i + j] == s2[j] && (i + j) < (n))
			{
				if (s1[i + j] == s2[j] && j + 1 == ft_strlen(s2))
					return (char *)(&s1[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
