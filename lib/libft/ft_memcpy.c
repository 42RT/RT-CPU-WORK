/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 13:59:40 by jrouilly          #+#    #+#             */
/*   Updated: 2013/11/26 14:39:56 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char		*ptrs1;
	const char	*ptrs2;

	ptrs1 = s1;
	ptrs2 = s2;
	while (n)
	{
		*ptrs1 = *ptrs2;
		++ptrs1;
		++ptrs2;
		--n;
	}
	return (s1);
}
