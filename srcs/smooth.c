/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 02:40:01 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 02:40:02 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gfx.h>
#include <raytracer.h>

static void	smooth_quickrender_mix(t_env *e, unsigned int x, unsigned int y)
{
	t_color	color;
	t_color	c2;

	color = gfx_get_pixel_color(e->gfx->buff[BUFF_NB],
								x - (x & 1), y - (y & 1));
	if (x < (e->set->width - 2) && y < (e->set->height - 2) && 0)
	{
		c2 = gfx_get_pixel_color(e->gfx->buff[BUFF_NB],
									x + (x & 1), y + (y & 1));
		color_mix_k(&color, c2, 127);
		color.a = 255;
	}
	gfx_pixel_put_to_image(e->gfx->buff[BUFF_NB], x, y, color);
}

void		smooth_quickrender(t_env *e)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < e->set->height)
	{
		x = 0;
		while (x < e->set->width)
		{
			if (*(e->worker_stop))
				return ;
			if (x < (e->set->width - 3))
				smooth_quickrender_mix(e, x + 1, y);
			if (y < (e->set->height - 3))
			{
				smooth_quickrender_mix(e, x, y + 1);
				if (x < (e->set->width - 3))
					smooth_quickrender_mix(e, x + 1, y + 1);
			}
			x += 2;
		}
		y += 2;
	}
}
