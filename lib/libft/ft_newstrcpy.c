/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newstrcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/29 08:54:53 by jrouilly          #+#    #+#             */
/*   Updated: 2014/01/29 08:57:32 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_newstrcpy(const char *s2)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = (char *)malloc((strlen(s2) + 1) * sizeof(char));
	while (*(s2 + i))
	{
		*(s1 + i) = *(s2 + i);
		++i;
	}
	*(s1 + i) = 0;
	return (s1);
}
