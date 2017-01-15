/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:03:31 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/31 20:40:01 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(dest + j))
		++j;
	while (*(src + i) && n)
	{
		*(dest + j + i) = *(src + i);
		++i;
		--n;
	}
	*(dest + j + i) = '\0';
	return (dest);
}
