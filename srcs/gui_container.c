/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_container.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:57:23 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/14 20:43:16 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		gui_container_bmp_set_n_display(t_gui *gui)
{
	CONTAINER->dest.x = 0;
	CONTAINER->dest.y = CONTAINER->up_lim;
	CONTAINER->dest.w = CONTAINER->surface->w;
	CONTAINER->dest.h = CONTAINER->surface->h;
	SDL_RenderCopy(gui->img, CONTAINER->bmp, NULL, &CONTAINER->dest);
	SDL_DestroyTexture(CONTAINER->bmp);
	SDL_FreeSurface(CONTAINER->surface);
}

void		gui_container_get_bmp(t_gui *gui, int type)
{
	if (type == DEF_GUI_CONTAINER_HEADER)
		CONTAINER->surface = SDL_LoadBMP("./ressources/container/header.bmp");
	else if (type == DEF_GUI_CONTAINER_MIDDLE)
		CONTAINER->surface = SDL_LoadBMP("./ressources/container/middle.bmp");
	else
		CONTAINER->surface = SDL_LoadBMP("./ressources/container/footer.bmp");
	if (!CONTAINER->surface)
		gui_error(2);
	CONTAINER->bmp = SDL_CreateTextureFromSurface(gui->img, CONTAINER->surface);
	if (!CONTAINER->bmp)
		gui_error(3);
}

void		gui_build_container(t_gui *gui, int mode, int px)
{
	int i;

	CONTAINER = (t_container *)malloc(sizeof(t_container));
	//gui_container_get_bmp(gui, px);
	if (mode == 1)
		CONTAINER->px = DEF_GUI_CONTAINER_RESIZED;
	else
		CONTAINER->px = px;
	CONTAINER->up_lim = gui->tmp_lim;
	CONTAINER->bot_lim = gui->tmp_lim + CONTAINER->px;
	gui->tmp_lim = CONTAINER->bot_lim;
	//gui_container_bmp_set_n_display(gui);
	i = 0;
	while (i < gui->width)
	{
		gui_color_set(gui, "container", "basic");
		gui_pixel_put(gui, i, gui->tmp_lim);
		i++;
	}
	gui->cbcnt++;
}
