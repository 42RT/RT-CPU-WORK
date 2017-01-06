/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:44:09 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/16 11:36:51 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && *s1 == *s2)
	{
		i++;
		s1++;
		s2++;
		if (!*s1 || !*s2)
			return (*(unsigned char*)s1 - *(unsigned char*)s2);
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
