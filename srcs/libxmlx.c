/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/21 22:20:02 by jrouilly          #+#    #+#             */
/*   Updated: 2017/01/23 12:51:21 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <libxmlx.h>

void			*libxmlx_init(char *title, int res_x, int res_y,
								unsigned int buff_nb)
{
	t_gfx			*res;
	unsigned int	i;

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
	i = -1;
	buff_nb = (buff_nb < 5 ? buff_nb : 4);
	while (++i < buff_nb)
		res->buff[i] = libxmlx_new_image(res, res_x, res_y);
	while (++i < 4)
		res->buff[i] = 0;
	res->act = 0;
	res->expose = 1;
	return (res->renderer ? (void *)res : 0);
}

void			libxmlx_loop(t_gfx *gfx)
{
	SDL_WaitEvent(&(gfx->event));
	//printf("EVENT QUEUE : %d\n", SDL_PeepEvents(&(gfx->event), 10, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT));
}

void			libxmlx_poll(t_gfx *gfx)
{
	SDL_PollEvent(&(gfx->event));
}

void			libxmlx_exit(t_gfx *gfx, int ex)
{
	SDL_DestroyRenderer(gfx->renderer);
	SDL_DestroyWindow(gfx->win);
	TTF_Quit();
	SDL_Quit();
	exit(ex);
}
