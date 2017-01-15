/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 13:04:24 by jrouilly          #+#    #+#             */
/*   Updated: 2013/11/26 19:25:07 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				result;
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	result = 0;
	if (n < 1 || (!s1 && !s2))
		return (0);
	if ((!s1 || !*s1) && *s2)
		return (-1);
	else if ((!s2 || !*s2) && *s1)
		return (1);
	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	while (*ptrs1 && *ptrs2 && n && !result)
	{
		if (*ptrs1 != *ptrs2)
			result = -1 + ((*ptrs1 > *ptrs2) << 1);
		else
		{
			++ptrs1;
			++ptrs2;
		}
		--n;
	}
	return (result);
}
