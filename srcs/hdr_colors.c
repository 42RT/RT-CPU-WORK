/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdr_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 00:22:41 by jrouilly          #+#    #+#             */
/*   Updated: 2017/03/12 00:22:42 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <hdr_colors.h>

void			color_add(t_color *src, t_color color,
							unsigned int k) // rajouter e
{
	int			c;

	src->a = color.a;
	c = color.r;
	c *= k;
	c >>= 8;
	src->r = limit_nb(c + src->r, 255);
	c = color.g;
	c *= k;
	c >>= 8;
	src->g = limit_nb(c + src->g, 255);
	c = color.b;
	c *= k;
	c >>= 8;
	src->b = limit_nb(c + src->b, 255);
}

t_color			mix_color(t_color c1, t_color c2)
{
	t_color		color;

	color.a = (c1.a >> 1) + (c2.a >> 1);
	color.r = (c1.r >> 1) + (c2.r >> 1);
	color.g = (c1.g >> 1) + (c2.g >> 1);
	color.b = (c1.b >> 1) + (c2.b >> 1);
	return (color);
}

void			color_mix_k(t_color *src, t_color color,
							unsigned int k)
{
	unsigned int	c[2];

	if (k > 255)
		return ;
	src->a = color.a;
	c[0] = (unsigned int)src->r;
	c[0] *= (255 - k);
	c[1] = (unsigned int)color.r;
	c[0] += c[1] * k;
	c[0] >>= 8;
	src->r = c[0];
	c[0] = (unsigned int)src->g;
	c[0] *= (255 - k);
	c[1] = (unsigned int)color.g;
	c[0] += c[1] * k;
	c[0] >>= 8;
	src->g = c[0];
	c[0] = (unsigned int)src->b;
	c[0] *= (255 - k);
	c[1] = (unsigned int)color.b;
	c[0] += c[1] * k;
	c[0] >>= 8;
	src->b = c[0];
}

t_color			color_attenuate(t_color color, float k)
{
	t_color		res;

	res.a = color.a;
	res.r = color.r * k;
	res.g = color.g * k;
	res.b = color.b * k;
	return (res);
}
