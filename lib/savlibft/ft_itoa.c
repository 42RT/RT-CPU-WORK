/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:52:12 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/01 10:47:19 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_str(char *str, int n, int start, int end)
{
	unsigned int	n2;

	if (n == 0)
		str[0] = '0';
	if (n > 0)
		n2 = n;
	if (n < 0)
	{
		str[0] = '-';
		n2 = -n;
		start++;
		end++;
	}
	while (start < end)
	{
		str[end - 1] = n2 % 10 + '0';
		n2 = n2 / 10;
		end--;
	}
}

char		*ft_itoa(int n)
{
	int				i;
	unsigned int	n2;
	char			*str;

	n2 = n;
	i = 0;
	if (n < 0)
		n2 = -n;
	while (n2 > 0)
	{
		n2 = n2 / 10;
		i++;
	}
	if ((str = ft_strnew(i + 1)) == NULL)
		return (NULL);
	ft_write_str(str, n, 0, i);
	return (str);
}
