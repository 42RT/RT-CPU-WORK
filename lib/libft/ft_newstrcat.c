/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newstrcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 17:14:46 by jrouilly          #+#    #+#             */
/*   Updated: 2014/02/06 17:51:27 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_newstrcat(char *dest, const char *src)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = -1;
	result = (char *) malloc((ft_strlen(dest) + ft_strlen(src) + 1)
								* sizeof(char));
	while (dest[++j])
		result[j] = dest[j];
	while (src[i])
	{
		result[i + j] = src[i];
		++i;
	}
	result[i + j] = '\0';
	return (result);
}
