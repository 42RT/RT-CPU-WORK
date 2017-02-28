/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:04:15 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/15 15:54:03 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*result;
	int		length;
	int		i;
	char	*s1;
	char	*s2;

	result = NULL;
	if (!haystack || !needle)
		return (NULL);
	s1 = (char *)haystack - 1;
	if (*(s1 + 1) == '\0' || *needle == '\0')
		return (s1 + 1);
	length = ft_strlen(haystack) - ft_strlen(needle);
	while (result == NULL && ++s1 <= (haystack + length))
	{
		s2 = (char *)needle;
		i = 0;
		while ((*(s1 + i++) == *s2) && *s2)
			++s2;
		result = (*s2 ? NULL : s1);
	}
	return (result);
}
