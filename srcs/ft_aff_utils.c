/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 03:16:37 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 03:16:37 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void		print_percentage(int percent)
{
	static int	old = 0;

	if (percent == -1)
	{
		ft_printf("\rRendering canceled !\n");
		return ;
	}
	if (percent != old)
	{
		ft_printf("%sRendering: %d ", (percent != 0 ? "\r" : ""), percent);
		ft_putchar('%');
		old = percent;
	}
	old %= 100;
}

void		print_time(unsigned int start)
{
	unsigned int		hour;
	unsigned int		min;
	unsigned int		sec;

	sec = (unsigned int)time(NULL) - start;
	min = sec / 60;
	sec %= 60;
	hour = min / 60;
	min %= 60;
	if (hour)
		printf("Rendering time: %u hour%s, %u minute%s and %u second%s.\n",
				hour, hour > 1 ? "s" : "", min, min > 1 ? "s" : "", sec,
				sec > 1 ? "s" : "");
	else if (min)
		printf("Rendering time: %u minute%s and %u second%s.\n", min,
				min > 1 ? "s" : "", sec, sec > 1 ? "s" : "");
	else if (sec)
		printf("Rendering time: %u second%s.\n", sec, sec > 1 ? "s" : "");
	else
		printf("Rendering time: <1 second.\n");
}
