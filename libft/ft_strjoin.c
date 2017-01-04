/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 17:52:01 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:18:28 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new;
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new)
	{
		while (s1[i] != '\0')
		{
			new[i] = s1[i];
			i++;
		}
		while (s2[i - ft_strlen(s1)] != '\0')
		{
			new[i] = s2[i - ft_strlen(s1)];
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}
