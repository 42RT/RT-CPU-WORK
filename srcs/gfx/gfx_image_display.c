/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_image_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 09:32:44 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/06 09:32:45 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <gfx.h>
#include <raytracer.h>


void			gfx_blitz_image(t_gfx *gfx, int x, int y, t_img *img)
{
	static int		*map = 0;
	int				i;
	static int		res = 0;
	SDL_Rect		dst;

	if (!gfx->expose)
		return ;
	dst.x = x;
	dst.y = y;
	dst.w = gfx->buff[0]->width;
	dst.h = gfx->buff[0]->height;
	if (res != dst.w * dst.h && map)
	{
		free(map);
		map = 0;
	}
	res = gfx->buff[0]->width * gfx->buff[0]->height;
	if (!map)
		map = (int *)malloc(res * sizeof(int));
	i = -1;
	while (++i < res)
		map[i] = *((int *)(img->data + i));
	SDL_UpdateTexture(gfx->texture, 0, map, 4 * gfx->buff[0]->width);
	SDL_RenderCopy(gfx->renderer, gfx->texture, 0, &dst);
}

void			gfx_blitz_black_image(t_gfx *gfx, int x, int y)
{
	int		i;
	int		j;

	SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 255);
	i = -1;
	while (++i + y < gfx->buff[0]->height)
	{
		j = -1;
		while (++j + x < gfx->buff[0]->width)
			SDL_RenderDrawPoint(gfx->renderer, j + x, i + y);
	}
	SDL_RenderPresent(gfx->renderer);
}

void			gfx_display_image(t_gfx *gfx, int x, int y, t_img *img)
{
	gfx_blitz_image(gfx, x, y, img);
	SDL_RenderPresent(gfx->renderer);
}
