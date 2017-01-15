/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:03:54 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/15 15:53:51 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	ch;
	int		i;

	if (c)
	{
		ptr = NULL;
		ch = (char)c;
		i = 0;
		while (*(s + i))
		{
			if (*(s + i) == ch)
				ptr = (char *)s + i;
			++i;
		}
		return (ptr);
	}
	else
		return ((char *)s + ft_strlen(s));
}
