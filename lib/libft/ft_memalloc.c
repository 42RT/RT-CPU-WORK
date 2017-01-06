/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:24:06 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/31 13:29:07 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	i = 0;
	mem = (void *)malloc(size * sizeof(*mem));
	if (mem == NULL)
		return (NULL);
	while (i < size)
	{
		((char*)mem)[i] = 0;
		++i;
	}
	return (mem);
}
