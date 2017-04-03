/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libxmlx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 03:35:58 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 03:35:59 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libxmlx.h>

// a refaire en alpha
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

void			libxmlx_flip_screen(t_gfx *gfx) // useless ??
{
	if (!gfx->expose)
		return ;
	//mlx_put_image_to_window(gfx->mlx, gfx->win, gfx->screen, 0, 0);
}

void			libxmlx_change_screen(t_gfx *gfx, unsigned int nb)
{
	if (nb > 0 || nb < 5)
		gfx->act = nb - 1;
	libxmlx_display_image(gfx, 0, 0, gfx->buff[gfx->act]);
}

t_gfx			*libxmlx_reload(t_gfx *gfx, int res_x, int res_y,
								int buff_nb)//////////////////////////////////////////////////////////////
{
	int		i;

	if (res_x != gfx->buff[0]->width || res_y != gfx->buff[0]->height)
	{
		gfx->expose = 0;
		SDL_SetWindowSize(gfx->win, res_x, res_y);
		i = -1;
		buff_nb = (buff_nb < 5 ? buff_nb : 4);
		while (++i < buff_nb)
		{
			libxmlx_destroy_image(gfx->buff[i]); // si buff (changement du nombre de buff)
			gfx->buff[i] = libxmlx_new_image(gfx, res_x, res_y);
		}
		while (++i < 4)
			gfx->buff[i] = 0;
		gfx->expose = 1;
	}
	return (gfx);
}
