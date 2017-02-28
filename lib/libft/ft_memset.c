/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 13:07:37 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/31 20:37:57 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char	*test;

	test = (char *)b;
	while (len)
	{
		*test = (char)c;
		++test;
		--len;
	}
	return ((void *)b);
}
