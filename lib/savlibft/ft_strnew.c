/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:26:40 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/11 14:05:34 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	if ((str = (char *)malloc((size + 1) * sizeof(*str))) == NULL)
		return (NULL);
	while (i <= size)
	{
		str[i] = '\0';
		++i;
	}
	return (str);
}
