/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:14:17 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:19:29 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = ft_strlen(s1);
	if (n == 0)
		return (s1);
	while (s2[i] != '\0' && i < n)
	{
		s1[ft_strlen(s1)] = s2[i];
		i++;
	}
	s1[i + j] = '\0';
	return (s1);
}
