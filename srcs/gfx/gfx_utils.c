/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 03:35:58 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 03:35:59 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gfx.h>

unsigned int	get_alpha_color(unsigned int origin, unsigned int color)
{
	unsigned int	res;
	int				k;

	k = 1 + ((color & 0xFF000000) >> 24);
	res = 0xFF00;
	res += (((origin & 0xFF0000) >> 16) * (255 - k)) >> 8;
	res += (((color & 0xFF0000) >> 16) * k) >> 8;
	res <<= 8;
	res += (((origin & 0xFF00) >> 8) * (255 - k)) >> 8;
	res += (((color & 0xFF00) >> 8) * k) >> 8;
	res <<= 8;
	res += ((origin & 0xFF) * (255 - k)) >> 8;
	res += ((color & 0xFF) * k) >> 8;
	return (res);
}

void			gfx_change_screen(t_gfx *gfx, unsigned int nb)
{
	if (nb > 0 || nb < 5)
		gfx->act = nb - 1;
	gfx_display_image(gfx, 0, 0, gfx->buff[gfx->act]);
}

t_gfx			*gfx_reload(t_gfx *gfx, int res_x, int res_y,
								int buff_nb)
{
	int		i;

	if (res_x != gfx->buff[0]->width || res_y != gfx->buff[0]->height)
	{
		gfx->expose = 0;
		SDL_SetWindowSize(gfx->win, res_x, res_y);
		SDL_DestroyTexture(gfx->texture);
		gfx->texture = SDL_CreateTexture(gfx->renderer,
											SDL_PIXELFORMAT_ARGB8888,
											SDL_TEXTUREACCESS_STREAMING,
											res_x, res_y);
		i = -1;
		buff_nb = (buff_nb < 5 ? buff_nb : 4);
		while (++i < buff_nb)
		{
			gfx_destroy_image(gfx->buff[i]);
			gfx->buff[i] = gfx_new_image(gfx, res_x, res_y);
		}
		while (++i < 4)
			gfx->buff[i] = 0;
		gfx->expose = 1;
	}
	return (gfx);
}
