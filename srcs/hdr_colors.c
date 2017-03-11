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

t_color				void_tcolor(void)
{
	t_color			res;

	res.r = 0;
	res.g = 0;
	res.b = 0;
	res.e = 0;
	res.a = 0xFF;
	return (res);
}

int					is_void_tcolor(t_color color)
{
	return (!(color.r || color.g || color.b));
}

/*t_color				color_add(t_color c1, t_color c2)
{
	t_color			res;
	t_color			*bigger;
	t_color			*lower;
	unsigned int	tmp[3];


	bigger = (c1.e > c2.e ? &c1 : &c2);
	lower = (c1.e > c2.e ? &c2 : &c1);
	res.e = bigger->e;
	tmp[0] = bigger->r + (lower->r >> (bigger->e - lower->e));
	tmp[1] = bigger->g + (lower->g >> (bigger->e - lower->e));
	tmp[2] = bigger->b + (lower->b >> (bigger->e - lower->e));
	if (tmp[0] > 255 || tmp[1] > 255 || tmp[2] > 255)
	{
		++res.e;
		tmp[0] >>= 1;
		tmp[1] >>= 1;
		tmp[2] >>= 1;
	}
	res.r = tmp[0];
	res.g = tmp[1];
	res.b = tmp[2];
	return (res);
}*/
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

/*t_color				color_add_k(t_color c1, t_color c2, float k)
{
	return (color_add(c1, color_attenuate(c2, k)));
}
*/

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
//	src->r = ((int)src->r * (255 - k) + ((int)color.r * k)) >> 8;
//	src->g = ((int)src->g * (255 - k) + ((int)color.g * k)) >> 8;
//	src->b = ((int)src->b * (255 - k) + ((int)color.b * k)) >> 8;
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

/*t_color				color_attenuate(t_color color, float k)
{
	while (k < 0.5 && color.e > -128)
	{
		k *= 2;
		--color.e;
	}
	color.r *= k;
	color.g *= k;
	color.b *= k;
	if (color.r < 128 && color.g < 128 && color.b < 128)
	{
		++color.e;
		color.r <<= 1;
		color.g <<= 1;
		color.b <<= 1;
	}
	return (color);
}*/