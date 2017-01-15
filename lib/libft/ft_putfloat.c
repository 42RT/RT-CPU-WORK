/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 14:54:50 by jrouilly          #+#    #+#             */
/*   Updated: 2014/11/28 14:54:50 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_putfloat(float nb)
{
	int		precision_min;

	precision_min = 6;
	ft_putnbr((int)nb);
	nb -= (int)nb;
	ft_putchar('.');
	while (--precision_min == 5 || (nb >= 0.000001 && precision_min > 0))
	{
		nb *= 10;
		ft_putnbr(ft_abs((int)nb));
		nb -= (int)nb;
	}
}