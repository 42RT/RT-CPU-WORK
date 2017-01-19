/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:48:19 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 16:39:18 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		gui_background_get_set_n_display(t_gui *gui)
{
	gui->bg_surface = SDL_LoadBMP("./ressources/gui_texture/font2.bmp");
	if (!gui->bg_surface)
		gui_error(2);
	gui->bg_bmp = SDL_CreateTextureFromSurface(gui->img, gui->bg_surface);
	if (!gui->bg_bmp)
		gui_error(3);
	gui->bg_dest.x = 0;
	gui->bg_dest.y = 0;
	gui->bg_dest.w = GUI_WIDTH;
	gui->bg_dest.h = gui->height;
	SDL_RenderCopy(gui->img, gui->bg_bmp, NULL, &gui->bg_dest);
	SDL_DestroyTexture(gui->bg_bmp);
	SDL_FreeSurface(gui->bg_surface);
}
