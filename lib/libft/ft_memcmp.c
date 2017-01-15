/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:57:43 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/12 15:21:17 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				result;
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	result = 0;
	ptrs1 = (unsigned char*)s1;
	ptrs2 = (unsigned char*)s2;
	while (n && (result == 0))
	{
		if (*ptrs1 != *ptrs2)
			result = *ptrs1 - *ptrs2;
		else
		{
			++ptrs1;
			++ptrs2;
		}
		--n;
	}
	return (result);
}
