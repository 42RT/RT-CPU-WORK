/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/19 16:56:37 by jrouilly          #+#    #+#             */
/*   Updated: 2014/01/29 09:15:16 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <libft.h>

t_pftype	*ft_printf_argnbr(char **str)
{
	t_pftype	*res;

	res = (t_pftype *)malloc(sizeof(t_pftype));
	res->nb = 0;
	res->zero = 0;
	if (**str == '0')
	{
		res->zero = 1;
		++(*str);
	}
	while (ft_isdigit(**str))
	{
		res->nb *= 10;
		res->nb += (int)(**str - 0x30);
		++(*str);
	}
	return (res);
}

void		ft_printf_spec(char **str, va_list *ap)
{
	t_pftype	*st;

	st = ft_printf_argnbr(str);
	(void)st;
	if (**str == 'd')
		ft_putnbr(va_arg(*ap, int));
	if (**str == 's')
		ft_putstr(va_arg(*ap, char*));
	if (**str == 'x')
		ft_putstr(ft_hextoa(va_arg(*ap, unsigned int)));
	if (**str == 'f')
		ft_putfloat(va_arg(*ap, double));
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*str;

	str = (char *)format;
	va_start(ap, format);
	while (*str)
	{
		while (*str != '%' && *str != '\0')
		{
			ft_putchar(*str);
			++str;
		}
		if (*str == '%')
		{
			++str;
			ft_printf_spec(&str, &ap);
			++str;
		}
	}
	va_end(ap);
	return (0);
}
