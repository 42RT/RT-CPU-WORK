/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 03:21:30 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 03:21:33 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gfx.h>

void		gfx_pixel_put_to_image(t_img *img, int x, int y,
									t_color color)
{
	if (color.a == 255 || 1)
		img->data[img->width * y + x] = color;
}

t_color		gfx_get_pixel_color(t_img *img, int x, int y)
{
	return (img->data[img->width * y + x]);
}

/*
** unused for now, need rework
*/

void		gfx_pixel_put(t_gfx *gfx, int x, int y, t_color color)
{
	SDL_SetRenderDrawColor(gfx->renderer, color.b, color.g,
									color.r, color.a);
	SDL_RenderDrawPoint(gfx->renderer, x, y);
}
