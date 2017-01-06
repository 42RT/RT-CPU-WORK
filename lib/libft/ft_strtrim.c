/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 18:05:44 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/01 11:29:11 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_stralloc(char *str, int k)
{
	if (k >= 0)
		if ((str = ft_strnew(k)) == NULL)
			return (NULL);
	if (k < 0)
		if ((str = ft_strnew(0)) == NULL)
			return (NULL);
	return (str);
}

char		*ft_strtrim(char const *s)
{
	int		l;
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = 0;
	str = NULL;
	l = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[l - j - 1] == ' ' || s[l - j - 1] == '\n' || s[l - j - 1] == '\t')
		j++;
	k = l - i - j;
	if ((str = ft_stralloc(str, k)) == NULL)
		return (NULL);
	while (i < l - j)
	{
		*str = ((char*)s)[i];
		str++;
		i++;
	}
	return (str - k);
}
