/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libxmlx_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 03:18:24 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 03:18:25 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libxmlx.h>

void			*libxmlx_new_image(t_gfx *gfx, int res_x, int res_y)
{
	t_img	*res;
	int		i;
	int		size;

	(void)gfx;
	res = (t_img *)malloc(sizeof(t_img));
	if (!res)
		return (0);
	res->width = res_x;
	res->height = res_y;
	size = res_y * res_x;
	res->data = (unsigned int *)malloc(size * sizeof(unsigned int));
	if (!res->data)
		return (0);
	i = -1;
	while (++i < size)
		res->data[i] = 0;
	return ((void *)res);
}

void			libxmlx_destroy_image(t_img *img)
{
	free(img->data);
	free(img);
}

void			libxmlx_blitz_image(t_gfx *gfx, int x, int y, t_img *img)
{
	char	color[4];
	int		i;
	int		j;

	if (!gfx->expose)
		return ;
	i = -1;
	while (++i + y < gfx->buff[0]->height && i < img->height)
	{
		j = -1;
		while (++j + x < gfx->buff[0]->width && j < img->width)
		{
			color[0] = 255;
			color[1] = img->data[img->width * i + j] >> 16; // masques binaires sur mac ??
			color[2] = img->data[img->width * i + j] >> 8;
			color[3] = img->data[img->width * i + j];
			SDL_SetRenderDrawColor(gfx->renderer, color[1], color[2], color[3], color[0]);
			SDL_RenderDrawPoint(gfx->renderer, j + x, i + y);
		}
	}
}

void			libxmlx_blitz_black_image(t_gfx *gfx, int x, int y)
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

void			libxmlx_display_image(t_gfx *gfx, int x, int y, t_img *img)
{
	libxmlx_blitz_image(gfx, x, y, img);
	SDL_RenderPresent(gfx->renderer);
}
