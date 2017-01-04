/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/06 16:39:51 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:20:53 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_strrev(char *s)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = 0;
	tmp = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i < len / 2)
		{
			tmp = s[i];
			s[i] = s[len - i - 1];
			s[len - i - 1] = tmp;
			i++;
		}
	}
	return (s);
}
