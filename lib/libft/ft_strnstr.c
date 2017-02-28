/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:03:47 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/15 16:01:57 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char			*result;
	int				length;
	unsigned int	i;
	char			*s1;
	char			*s2;

	result = NULL;
	if (haystack == NULL || needle == NULL)
		return (NULL);
	s1 = (char *)haystack - 1;
	if (*haystack == '\0' || *needle == '\0')
		return ((char *)haystack);
	length = ft_strlen(haystack) - ft_strlen(needle);
	while (result == NULL && ++s1 < (haystack + length) && len > 0)
	{
		s2 = (char *)needle;
		i = 0;
		while ((*(s1 + i) == *s2) && *s2 && (i < len))
		{
			++s2;
			++i;
		}
		result = ((i < len) && (*s2) ? NULL : s1);
	}
	return (result);
}
