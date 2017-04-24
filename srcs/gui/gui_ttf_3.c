/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_ttf_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:40:46 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:22 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_freetxt_write(t_freetxt *freetxt, char *color)
{
	t_gui	*gui;

	gui = get_gui();
	gui_txt_to_texture(freetxt->txt->content, "SOLID", color);
	TTF->rect.x = freetxt->dest.x;
	TTF->rect.y = freetxt->dest.y;
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
}

void	gui_write_textbox_value(t_gui *gui, t_textbox *textbox, char *color)
{
	gui_txt_to_texture(textbox->value, "BLENDED", color);
	if (textbox->value[0] == ' ')
		TTF->rect.x = textbox->dest.x + 2;
	else
		TTF->rect.x = textbox->dest.x + 3;
	TTF->rect.y = textbox->dest.y + ((textbox->dest.h - TTF->h_px) / 2);
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
}

void	gui_write_help(t_gui *gui, char *text, int align, int y)
{
	gui_txt_to_texture(text, "SOLID", "white");
	if (align == GUI_ALIGN_LEFT)
		TTF->rect.x = HELP->dest.x + 10;
	else if (align == GUI_ALIGN_MID)
		TTF->rect.x = HELP->dest.x + (HELP->dest.w / 2) - (TTF->w_px / 2);
	else if (align == GUI_ALIGN_RIGHT)
		TTF->rect.x = HELP->dest.x + HELP->dest.w - TTF->w_px - 10;
	else
		TTF->rect.x = align;
	TTF->rect.y = y;
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
}
