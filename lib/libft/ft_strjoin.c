/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:02:08 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/31 20:46:31 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*ptr1;
	char	*ptr2;

	result = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)
					* sizeof(char));
	ptr1 = (char *)s1;
	ptr2 = result;
	while (*ptr1)
	{
		*ptr2 = *ptr1;
		++ptr2;
		++ptr1;
	}
	ptr1 = (char *)s2;
	while (*ptr1)
	{
		*ptr2 = *ptr1;
		++ptr1;
		++ptr2;
	}
	*ptr2 = '\0';
	return (result);
}
