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

int			init_th_data(t_th_data *data, t_env *e, int nb)
{
	data->e = e;
	data->nb = nb;
	data->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (0);
}

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
		ft_printf("Rendering time: %d hour%s, %d minute%s and %d second%s.\n",
				hour, hour > 1 ? "s" : "", min, min > 1 ? "s" : "", sec,
				sec > 1 ? "s" : "");
	else if (min)
		ft_printf("Rendering time: %d minute%s and %d second%s.\n", min,
				min > 1 ? "s" : "", sec, sec > 1 ? "s" : "");
	else if (sec)
		ft_printf("Rendering time: %d second%s.\n", sec, sec > 1 ? "s" : "");
	else
		ft_printf("Rendering time: <1 second.\n");
}
