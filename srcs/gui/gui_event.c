/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_pending_action_prevent(t_gui *gui)
{
	SDL_Surface	*surf;
	SDL_Texture	*bmp;
	SDL_Rect	dest;

	dest.x = 0;
	dest.y = 0;
	dest.w = gui->dest.w;
	dest.h = gui->dest.h;
	gui->action = 1;
	surf = SDL_LoadBMP("./ressources/gui_texture/help_black.bmp");
	if (!surf)
		gui_error(2);
	bmp = SDL_CreateTextureFromSurface(gui->img, surf);
	if (!bmp)
		gui_error(3);
	SDL_SetTextureBlendMode(bmp, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(bmp, 200);
	SDL_RenderCopy(gui->img, bmp, NULL, &dest);
	SDL_DestroyTexture(bmp);
	SDL_FreeSurface(surf);
	SDL_RenderPresent(gui->img);
}

void	event_widget_deselect(t_gui *gui)
{
	if (*(int *)WIDGET == TXB)
		event_txb_deselect(gui);
	else if (*(int *)WIDGET == SCL)
		gui_scroll_toggle(gui, (t_scroll *)gui->widget_active);
}
