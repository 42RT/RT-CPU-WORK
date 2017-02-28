/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:03:15 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/31 20:39:45 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(ft_strlen((char *)s) * sizeof(char));
	while (*(s + i))
	{
		*(result + i) = (*f)(i, *(s + i));
		++i;
	}
	return (result);
}
