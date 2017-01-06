/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:53:06 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/07 15:17:41 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoingnl(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	len;
	char			*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	len = i;
	i = 0;
	while (s2[i])
	{
		str[len + i] = s2[i];
		i++;
	}
	free(s1);
	free(s2);
	return (str);
}
