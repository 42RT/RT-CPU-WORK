/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:49:17 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/31 20:39:18 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

size_t	ft_strlen(const char *s)
{
	char	*str;
	size_t	result;

	str = (char*)s;
	result = 0;
	while (*str)
	{
		++str;
		++result;
	}
	return (result);
}
