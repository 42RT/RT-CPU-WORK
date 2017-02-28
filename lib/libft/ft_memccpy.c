/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:10:40 by jrouilly          #+#    #+#             */
/*   Updated: 2013/11/26 14:40:08 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned char		*ptrs1;
	const unsigned char	*ptrs2;
	int					stop;

	stop = 0;
	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	while (n && !stop)
	{
		*ptrs1 = *ptrs2;
		if (*ptrs2 == (unsigned char)c)
			stop = 1;
		++ptrs1;
		++ptrs2;
		--n;
	}
	if (stop)
		return (ptrs1);
	else
		return (NULL);
}
