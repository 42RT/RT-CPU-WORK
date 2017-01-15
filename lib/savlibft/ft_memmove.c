/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:40:08 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/03 18:12:52 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = ((char*)src)[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		((char*)dst)[i] = str[i];
		i++;
	}
	ft_strdel(&str);
	return (dst);
}
