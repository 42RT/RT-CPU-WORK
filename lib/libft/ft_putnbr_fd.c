/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:13:22 by rfriscca          #+#    #+#             */
/*   Updated: 2015/11/30 17:42:07 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n2;

	if (n >= 0)
		n2 = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n2 = -n;
	}
	if (n2 > 9)
	{
		ft_putnbr_fd(n2 / 10, fd);
		ft_putnbr_fd(n2 % 10, fd);
	}
	if (n2 <= 9)
		ft_putchar_fd(n2 + 48, fd);
}
