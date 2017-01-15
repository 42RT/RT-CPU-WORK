/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 02:26:22 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/18 02:26:23 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned int	ft_hextoi(char *str)
{
	unsigned int	res;

	res = 0;
	if (!str || *str != '0' || *++str != 'x')
		return (res);
	++str;
	while (ft_ishex(*str))
	{
		res <<= 4;
		res += ft_hexval(*(str++));
	}
	return (res);
}