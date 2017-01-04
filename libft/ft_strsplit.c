/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 20:38:24 by rdieulan          #+#    #+#             */
/*   Updated: 2016/11/21 15:34:26 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

unsigned int		ft_nword(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nword;

	nword = 0;
	i = 0;
	if (s[i] != c)
	{
		nword++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == c)
			if (s[i + 1] != c)
				nword++;
		i++;
	}
	return (nword);
}

static char			**ft_dosplit(char const *s, char c, int nword, int i)
{
	char			**result;
	int				start;

	start = 0;
	result = (char **)malloc(sizeof(char *) * nword + 1);
	if (!result)
		return (NULL);
	nword = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
			i++;
		else
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			result[nword] = ft_strsub(s, start, (i - start));
			if (!result)
				return (NULL);
			nword++;
		}
	}
	result[nword] = NULL;
	return (result);
}

char				**ft_strsplit(char const *s, char c)
{
	unsigned int	nword;

	if (!s || !c)
		return (NULL);
	nword = ft_nword(s, c);
	return (ft_dosplit(s, c, nword, 0));
}
