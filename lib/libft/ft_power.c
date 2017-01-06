/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 14:33:27 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/15 14:55:04 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_power(int n, int pow)
{
	int		i;
	int		n2;

	i = 1;
	if (pow == 0)
		n2 = 1;
	if (pow > 0)
		n2 = n;
	if (pow < 0)
		ft_putstr("Error ft_power don't handle negative power cases");
	while (i < pow)
	{
		n2 = n2 * n;
		++i;
	}
	return (n2);
}
