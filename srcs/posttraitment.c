/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posttraitment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 05:55:07 by jrouilly          #+#    #+#             */
/*   Updated: 2017/04/28 05:55:08 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

static t_color	pt_luminosity(t_color c, float k)
{
	int		tmp;

	if (k <= 0)
		return (int_to_tcolor(0));
	tmp = c.r;
	tmp *= k;
	c.r = limit_nb(tmp, 255);
	tmp = c.g;
	tmp *= k;
	c.g = limit_nb(tmp, 255);
	tmp = c.b;
	tmp *= k;
	c.b = limit_nb(tmp, 255);
	return (c);
}

static t_color	pt_contrast(t_color c, float k)
{
	int		tmp;

	if (k <= 0)
		return (int_to_tcolor(0));
	tmp = c.r;
	tmp = (tmp - 128) * k;
	c.r = limit_nb(tmp < -128 ? 0 : tmp + 128, 255);
	tmp = c.g;
	tmp = (tmp - 128) * k;
	c.g = limit_nb(tmp < -128 ? 0 : tmp + 128, 255);
	tmp = c.b;
	tmp = (tmp - 128) * k;
	c.b = limit_nb(tmp < -128 ? 0 : tmp + 128, 255);
	return (c);
}

static t_color	pt_saturation(t_color c, float k)
{
	int		tmp;
	int		mean;

	if (k <= 0)
		return (int_to_tcolor(0));
	mean = c.r + c.g + c.b;
	mean /= 3;
	tmp = c.r;
	tmp = (tmp - mean) * k;
	c.r = limit_nb(tmp < -mean ? 0 : tmp + mean, 255);
	tmp = c.g;
	tmp = (tmp - mean) * k;
	c.g = limit_nb(tmp < -mean ? 0 : tmp + mean, 255);
	tmp = c.b;
	tmp = (tmp - mean) * k;
	c.b = limit_nb(tmp < -mean ? 0 : tmp + mean, 255);
	return (c);
}

void			posttraitment(t_env *e)
{
	unsigned int	x;
	unsigned int	y;
	t_color			c;

	y = 0;
	while (y < e->set->height)
	{
		x = 0;
		while (x < e->set->width)
		{
			c = gfx_get_pixel_color(e->gfx->buff[BUFF_NB], x, y);
			if (e->set->contrast != 0.5)
				c = pt_contrast(c, log(e->set->contrast + 0.5) / 2 + 1);
			if (e->set->saturation != 0.5)
				c = pt_saturation(c, exp(e->set->saturation * 2 - 1));
			if (e->set->luminosity != 0)
				c = pt_luminosity(c, exp(e->set->luminosity));
			gfx_pixel_put_to_image(e->gfx->buff[e->gfx->act], x, y, c);
			x++;
		}
		y++;
	}
	gfx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
}
