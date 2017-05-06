/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/21 22:20:02 by jrouilly          #+#    #+#             */
/*   Updated: 2017/01/23 12:51:21 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <gfx.h>

static void		init_gfx_buffers(t_gfx *gfx, int buff_nb, int res_x, int res_y)
{
	int				i;

	i = -1;
	buff_nb = (buff_nb < 6 ? buff_nb : 5);
	while (++i < buff_nb)
		gfx->buff[i] = gfx_new_image(gfx, res_x, res_y);
	while (++i < 8)
		gfx->buff[i] = 0;
}

t_gfx			*gfx_init(char *title, int res_x, int res_y, int buff_nb)
{
	t_gfx			*res;

	res = (void *)malloc(sizeof(t_gfx));
	res->title = ft_strdup(title);
	if (SDL_Init(SDL_INIT_VIDEO))
		return ((void *)(intptr_t)ft_error("Failed to init SDL"));
	if (TTF_Init())
		return ((void *)(intptr_t)ft_error("Failed to init SDL TTF"));
	res->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, res_x, res_y, SDL_WINDOW_SHOWN);
	res->winID = SDL_GetWindowID(res->win);
	if (!res->win)
		return (0);
	res->renderer = SDL_CreateRenderer(res->win, -1, SDL_RENDERER_ACCELERATED);
	res->texture = SDL_CreateTexture(res->renderer, SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										res_x, res_y);
	init_gfx_buffers(res, buff_nb, res_x, res_y);
	res->act = 0;
	res->expose = 1;
	return (res->renderer ? res : 0);
}

int				gfx_loop(t_gfx *gfx)
{
	return (SDL_WaitEvent(&(gfx->event)));
}

int				gfx_poll(t_gfx *gfx)
{
	return (SDL_PollEvent(&(gfx->event)));
}

void			gfx_exit(t_gfx *gfx, int ex)
{
	SDL_DestroyTexture(gfx->texture);
	SDL_DestroyRenderer(gfx->renderer);
	SDL_DestroyWindow(gfx->win);
	TTF_Quit();
	SDL_Quit();
	exit(ex);
}
