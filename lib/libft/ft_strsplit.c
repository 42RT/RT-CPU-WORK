/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:04:07 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/30 19:14:34 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*split_strcpy(char **s, char c)
{
	char	*result;
	char	*ptr;
	int		size;

	while (**s == c)
		++(*s);
	ptr = *s;
	size = 0;
	while (*ptr != c && *ptr)
	{
		++size;
		++ptr;
	}
	result = (char *)malloc((size + 1) * sizeof(char));
	ptr = result;
	while (**s != c && **s)
	{
		*ptr = **s;
		++(*s);
		++ptr;
	}
	*ptr = '\0';
	return (result);
}

char		**ft_strsplit(char const *s, char c)
{
	int		nb;
	int		i;
	char	*s1;
	char	**result;

	s1 = (char *)s;
	nb = (*s1 != c);
	i = 0;
	while (*++s1)
		nb += (*s1 != c && *(s1 - 1) == c);
	result = (char **)malloc((nb + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	s1 = (char *)s;
	while (i < nb)
	{
		*(result + i) = split_strcpy(&s1, c);
		if (*(result + i) == NULL)
			return (NULL);
		++i;
	}
	*(result + i) = 0;
	return (result);
}
