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

#include <gui.h>

void		gui_background_get_set_n_display(t_gui *gui)
{
	char	*path;

	path = ft_strjoin(PATH->texture, "bg_deadrealm.bmp");
	BG->surface = SDL_LoadBMP(path);
	free(path);
	if (!BG->surface)
		gui_error(2);
	BG->bmp = SDL_CreateTextureFromSurface(gui->img, BG->surface);
	if (!BG->bmp)
		gui_error(3);
	BG->dest.x = 0;
	BG->dest.y = 0;
	BG->dest.w = gui->dest.w;
	BG->dest.h = gui->dest.h;
	SDL_RenderCopy(gui->img, BG->bmp, NULL, &BG->dest);
	SDL_DestroyTexture(BG->bmp);
	SDL_FreeSurface(BG->surface);
}
