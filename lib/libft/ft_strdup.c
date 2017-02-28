/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:53:52 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/15 15:53:13 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <libft.h>

char	*ft_strdup(const char *s1)
{
	size_t	length;
	char	*s2;

	length = ft_strlen(s1);
	s2 = (char *)malloc((length + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s1, length);
	*(s2 + length) = 0;
	return (s2);
}
