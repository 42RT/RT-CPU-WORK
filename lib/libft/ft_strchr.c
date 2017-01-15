/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:56:59 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/15 15:53:40 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	ch;
	int		i;

	if (c)
	{
		ptr = (char *)s;
		ch = (char)c;
		i = 0;
		while (*(s + i) && (*(s + i) != ch))
			++i;
		ptr = (*(s + i) != 0 ? ptr + i : NULL);
		return (ptr);
	}
	else
		return ((char *)s + ft_strlen(s));
}
