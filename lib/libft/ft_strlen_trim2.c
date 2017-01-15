/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_trim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 08:37:23 by jrouilly          #+#    #+#             */
/*   Updated: 2014/11/28 08:37:23 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen_trim2(char *str)
{
	size_t	size;

	size = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\r' || *str == '\t'
					 || *str == ':' || *str == ';'))
		++str;
	while (*str && *str != ' ' && *str != '\n' && *str != '\r' && *str != '\t'
			 && *str != ':' && *str != ';')
	{
		++str;
		++size;
	}
	if (*str == ':' || *str == ';')
		++size;
	return (size);
}