/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libxmlx_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 03:21:30 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 03:21:33 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libxmlx.h>

void			libxmlx_pixel_put_to_image(t_img *img, int x, int y,
											unsigned int color)
{
	if (!(color >> 24) || (color >> 24) == 255)
		img->data[img->width * y + x] = color;
	else
		img->data[img->width * y + x] = get_alpha_color(img->data[img->width
														* y + x], color);
}

unsigned int	libxmlx_get_pixel_color(t_img *img, int x, int y)
{
	return ((unsigned int)img->data[img->width * y + x]);
}

void			libxmlx_pixel_put(t_gfx *gfx, int x, int y, unsigned int color)
{
	(void)gfx;
	(void)x;
	(void)y;
	(void)color;
	//mlx_pixel_put(gfx->mlx, gfx->win, x, y, color);
}
