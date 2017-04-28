/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 03:18:24 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 03:18:25 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <gfx.h>
#include <raytracer.h>

t_img			*gfx_new_image(t_gfx *gfx, int res_x, int res_y)
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
	res->data = (t_color *)malloc(size * sizeof(t_color));
	if (!res->data)
		return (0);
	i = -1;
	while (++i < size)
		res->data[i] = int_to_tcolor(0);
	return ((void *)res);
}

void			gfx_destroy_image(t_img *img)
{
	free(img->data);
	free(img);
}

void			gfx_blitz_image(t_gfx *gfx, int x, int y, t_img *img)
{
	int				i;
	int				j;
	unsigned int	color[4];

	if (!gfx->expose)
		return ;
	i = -1;
	while (++i + y < gfx->buff[0]->height && i < img->height)
	{
		j = -1;
		while (++j + x < gfx->buff[0]->width && j < img->width)
		{
			color[0] = img->data[img->width * i + j].a;
			color[1] = img->data[img->width * i + j].r; // masques binaires sur mac ??
			color[2] = img->data[img->width * i + j].g;
			color[3] = img->data[img->width * i + j].b;
			SDL_SetRenderDrawColor(gfx->renderer, color[1], color[2],
									color[3], color[0]);
			SDL_RenderDrawPoint(gfx->renderer, j + x, i + y);
		}
	}
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

void			gfx_fill_image(t_img *img, unsigned int width,
								unsigned int height, t_color color)
{
	unsigned int	x;
	unsigned int	y;

	y = height;
	while (y--)
	{
		x = width;
		while (x--)
			img->data[img->width * y + x] = color;
	}
}
