/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:53:43 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/12 15:21:04 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*result;
	char	*ptr;

	result = (void *)malloc(size);
	if (result == NULL)
		return (NULL);
	ptr = (char *)result;
	while (size--)
		*(ptr + size) = 0;
	return (result);
}
