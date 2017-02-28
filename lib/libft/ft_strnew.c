/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:03:39 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/12 15:23:44 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*result;

	size += (size != 0);
	if (size)
	{
		result = (char *)malloc(size * sizeof(char));
		if (result == NULL)
			return (NULL);
		while (size)
			*(result + --size) = '\0';
		return (result);
	}
	else
		return (NULL);
}
