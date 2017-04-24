/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 21:49:16 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/29 21:49:17 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*ft_atoi_filter(const char *str)
{
	char	*ptr;

	ptr = (char *)str;
	while ((*ptr < 0x30 || *ptr >= 0x3A) && *ptr != '-')
	{
		if (*ptr == ' ' || *ptr == '+' || (*ptr > 0x06 && *ptr <= 0x0D))
			++ptr;
		else
			return (0);
	}
	return (ptr);
}

int			ft_atoi(const char *str)
{
	int		result;
	int		negatif;
	char	*ptr;

	result = 0;
	ptr = ft_atoi_filter(str);
	if (ptr == 0)
		return (0);
	negatif = (*ptr == 0x2D);
	if (negatif)
		++ptr;
	if (*ptr == ' ' && ptr)
		++ptr;
	while (*ptr >= 0x30 && *ptr < 0x3A)
	{
		result *= 10;
		result += (int)*ptr - 0x30;
		++ptr;
	}
	if (negatif)
		result = -result;
	return (result);
}
