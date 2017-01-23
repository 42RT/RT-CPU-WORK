/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_container.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:57:23 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 16:39:44 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		gui_container_display(t_gui *gui)
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
	(void)type;
	CONTAINER->surface = SDL_LoadBMP("./ressources/gui_texture/container.bmp");
	if (!CONTAINER->surface)
		gui_error(2);
	CONTAINER->bmp = SDL_CreateTextureFromSurface(gui->img, CONTAINER->surface);
	if (!CONTAINER->bmp)
		gui_error(3);
}

void		gui_container_init(t_gui *gui)
{
	if ((CONTAINER = (t_container *)malloc(sizeof(t_container))) == NULL)
		error(1);
	CONTAINER->surface = NULL;
	CONTAINER->bmp = NULL;
	CONTAINER->button = NULL;
	CONTAINER->scroll = NULL;
	CONTAINER->textbox = NULL;
}

void		gui_container_draw_lim(t_gui *gui)
{
	int i;
	
	i = 0;
	while (i < gui->width)
	{
		gui->color = gui_color("white");
		gui_pixel_put(gui, i, gui->tmp_lim);
		i++;
	}

}

void		gui_container_build(t_gui *gui, int mode, int px)
{
	gui_container_init(gui);
	//gui_container_get_bmp(gui, px);
	if (mode == 1)
		CONTAINER->px = GUI_CONTAINER_RESIZED;
	else
		CONTAINER->px = px;
	CONTAINER->up_lim = gui->tmp_lim;
	CONTAINER->bot_lim = gui->tmp_lim + CONTAINER->px;
	gui->tmp_lim = CONTAINER->bot_lim;
	//gui_container_draw_lim(gui);
	//gui_container_display(gui);
	gui->cbcnt++;
}
