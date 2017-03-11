/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdr_colors_convert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 00:24:26 by jrouilly          #+#    #+#             */
/*   Updated: 2017/03/12 00:24:26 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <hdr_colors.h>

t_color				rgb_to_tcolor(unsigned int r, unsigned int g,
									unsigned int b)
{
	t_color			res;

	res.r = r;
	res.g = g;
	res.b = b;
	res.e = 0;
	res.a = 0xFF;
	return (res);
}

t_color				int_to_tcolor(unsigned int color)
{
	t_color			res;

	res.r = (color >> 16) & 0xFF;
	res.g = (color >> 8) & 0xFF;
	res.b = color & 0xFF;
	res.e = 0;
	res.a = 0xFF;
	return (res);
}

unsigned int		tcolor_to_int(t_color color)
{
	unsigned int	res;

	res = color.a;
	res <<= 8;
	res += color.r;
	res <<= 8;
	res += color.g;
	res <<= 8;
	res += color.b;
	return (res);
}

t_color				get_color(char *str)
{
	int				val;
	t_color			res;

	if (str && *str)
	{
		if (*str == '0' && *(str + 1) == 'x')
			val = ft_hextoi(str);
		else
			val = ft_atoi(str);
	}
	else
		return (void_tcolor());
	res.r = ((val >> 16) & 0xFF);
	res.g = ((val >> 8) & 0xFF);
	res.b = (val & 0xFF);
	res.a = 255;
	res.e = 0;
	return (res);
}
