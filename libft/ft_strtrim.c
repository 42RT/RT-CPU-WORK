/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 19:09:00 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:21:38 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_end(char const *s)
{
	int		end;

	end = ft_strlen(s) - 1;
	if (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
	{
		while (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
			end--;
	}
	return (end);
}

static int	ft_start(char const *s)
{
	int		start;

	start = 0;
	if (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
	{
		while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
			start++;
	}
	return (start);
}

char		*ft_strtrim(char const *s)
{
	int		len;
	int		score;

	score = 0;
	if (!s)
		return (NULL);
	if (ft_start(s) > 0)
		score++;
	if (ft_end(s) < (int)(ft_strlen(s) - 1))
		score++;
	if (score > 0)
	{
		if (ft_end(s) <= ft_start(s))
			return (ft_strnew(1));
		len = ft_end(s) - ft_start(s) + 1;
		if (len < 0)
			return (ft_strnew(1));
		return (ft_strsub(s, ft_start(s), len));
	}
	return (ft_strdup(s));
}
