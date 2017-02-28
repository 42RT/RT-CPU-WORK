/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/16 18:49:43 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/09 12:28:08 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <raytracer.h>

void			color_add(unsigned int *src, unsigned int color,
							unsigned int k)
{
	int			c;
	int			res;

	res = (color >> 24) & 0xFF;
	res <<= 8;
	c = (color >> 16) & 0xFF;
	c *= k;
	c >>= 8;
	res |= limit_nb(c + ((*src >> 16) & 0xFF), 255);
	res <<= 8;
	c = (color >> 8) & 0xFF;
	c *= k;
	c >>= 8;
	res |= limit_nb(c + ((*src >> 8) & 0xFF), 255);
	res <<= 8;
	c = color & 0xFF;
	c *= k;
	c >>= 8;
	res |= limit_nb(c + (*src & 0xFF), 255);
	*src = res;
}

void			color_mix_k(unsigned int *src, unsigned int color,
							unsigned int k)
{
	unsigned int	c[4];

	if (k > 255)
		return ;
	c[0] = (color >> 24) & 0xFF;
	c[1] = (((*src >> 16) & 0xFF) * (255 - k)
			+ ((color >> 16) & 0xFF) * k) >> 8;
	c[2] = (((*src >> 8) & 0xFF) * (255 - k) + ((color >> 8) & 0xFF) * k) >> 8;
	c[3] = ((*src & 0xFF) * (255 - k) + (color & 0xFF) * k) >> 8;
	*src = c[0] << 24 | c[1] << 16 | c[2] << 8 | c[3];
}

unsigned int	color_attenuate(unsigned int color, float k)
{
	unsigned int	res;
	unsigned int	c;

	res = color & 0xFF000000;
	c = (unsigned int)((color & 0xFF0000) * k) & 0xFF0000;
	res |= c & 0xFF0000;
	c = (unsigned int)((color & 0xFF00) * k) & 0xFF00;
	res |= c & 0xFF00;
	c = (unsigned int)((color & 0xFF) * k) & 0xFF;
	res |= c & 0xFF;
	return (res);
}

unsigned int	get_color(char *str)
{
	if (str && *str)
	{
		if (*str == '0' && *(str + 1) == 'x')
			return (ft_hextoi(str));
		else
			return (ft_atoi(str));
	}
	else
		return (0);
}

unsigned int	mod_light(unsigned int color, float dst, float coef2)
{
	float			coef;
	unsigned int	res;

	res = color & 0xFF000000;
	coef = (1 + coef2) / (dst / 100 + coef2);
	res += ((int)((color & 0xFF) * coef)) & 0xFF;
	res += ((int)((color & 0xFF00) * coef)) & 0xFF00;
	res += ((int)(((color >> 16) & 0xFF) * coef) << 16) & 0xFF0000;
	return (res);
}
