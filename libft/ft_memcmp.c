/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:37:44 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:13:23 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *cp1 = s1;
	const unsigned char *cp2 = s2;

	while (n--)
	{
		if (*cp1 != *cp2)
			return (*cp1 - *cp2);
		else
		{
			cp1++;
			cp2++;
		}
	}
	return (0);
}
