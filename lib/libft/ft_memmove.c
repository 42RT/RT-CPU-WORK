/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:34:54 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/15 15:52:46 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char		*ptrs1;
	const char	*ptrs2;
	char		*buffer;

	ptrs1 = s1;
	ptrs2 = s2;
	buffer = (char *)malloc(n * sizeof(char));
	ft_memcpy(buffer, ptrs2, n);
	ft_memcpy(ptrs1, buffer, n);
	free(buffer);
	return (s1);
}
