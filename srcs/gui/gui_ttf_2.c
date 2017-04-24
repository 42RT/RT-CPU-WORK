/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_ttf_2.c                                        :+:      :+:    :+:   */
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
	TTF_SizeText(TTF->font, freetxt->txt->content, &TTF->w_px, &TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img,
		TTF_RenderText_Solid(TTF->font, freetxt->txt->content,
		gui_color(color)));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	TTF->rect.x = freetxt->dest.x;
	TTF->rect.y = freetxt->dest.y;
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
}

void	gui_container_write_txt(void *widget, char *color)
{
	int		cx;
	t_gui	*gui;

	gui = get_gui();
	if (((REF *)widget)->nature == CNT)
		cx = ((REF *)widget)->dest.x;
	else if (((REF *)widget)->p > -1)
		cx = BLOCK[((REF *)widget)->p]->dest.x;
	else if (((REF *)widget)->nature == PRM)
		cx = PARAM->dest.x;
	else
		cx = HELP->dest.x;
	TTF_SizeText(TTF->font, ((REF *)widget)->txt->content, &TTF->w_px,
		&TTF->h_px);
	TTF->texture = gui_txt_to_texture(((REF *)widget)->txt->content, color);
	//TTF->texture = SDL_CreateTextureFromSurface(gui->img,
	//	TTF_RenderText_Solid(TTF->font, ((REF *)widget)->txt->content,
	//	gui_color(color)));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	if (((REF *)widget)->txt->align == GUI_ALIGN_LEFT)
		TTF->rect.x = cx + GUI_FONT_BORDER_STEP;
	else if (((REF *)widget)->txt->align == GUI_ALIGN_MID)
		TTF->rect.x = cx + (GUI_WIDTH / 2) - (TTF->w_px / 2);
	else if (((REF *)widget)->txt->align == GUI_ALIGN_RIGHT)
		TTF->rect.x = cx + GUI_WIDTH - TTF->w_px - GUI_FONT_BORDER_STEP;
	else
		TTF->rect.x = ((REF *)widget)->txt->align;
	if (((REF *)widget)->nature == CNT)
		TTF->rect.y = ((REF *)widget)->dest.y + 10;
	else
		TTF->rect.y = ((REF *)widget)->dest.y + ((((REF *)widget)->dest.h -
			TTF->h_px - 4) / 2);
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
}

void	gui_widget_write_anchored_txt(t_gui *gui, void *widget, char *color)
{
	TTF_SizeText(TTF->font, ((REF *)widget)->txt->content, &TTF->w_px,
		&TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img,
		TTF_RenderText_Solid(TTF->font, ((REF *)widget)->txt->content,
			gui_color(color)));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	if (((REF *)widget)->txt->align == GUI_ALIGN_LEFT)
		TTF->rect.x = ((REF *)widget)->dest.x - TTF->w_px
			- GUI_FONT_BORDER_STEP;
	else if (((REF *)widget)->txt->align == GUI_ALIGN_MID)
		TTF->rect.x = ((REF *)widget)->dest.x 
			+ ((((REF *)widget)->dest.w - TTF->w_px) / 2);
	else if (((REF *)widget)->txt->align == GUI_ALIGN_RIGHT)
		TTF->rect.x = GUI_WIDTH - TTF->w_px - GUI_FONT_BORDER_STEP;
	else
		TTF->rect.x = ((REF *)widget)->dest.x;
	TTF->rect.y = ((REF *)widget)->dest.y
		+ ((((REF *)widget)->dest.h - TTF->h_px - 4) / 2);
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
}

void	gui_widget_write_txt(void *widget, char *color)
{
	t_gui	*gui;

	gui = get_gui();
	if (!ft_strcmp(((REF *)widget)->txt->anchor, "this"))
		gui_widget_write_anchored_txt(gui, widget, color);
	else
		gui_container_write_txt(widget, color);
}

void	gui_write_textbox_value(t_gui *gui, t_textbox *textbox, char *color)
{
	TTF_SizeText(TTF->font, textbox->value, &TTF->w_px, &TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img,
		TTF_RenderText_Blended(TTF->font, textbox->value, gui_color(color)));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
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
	TTF_SizeText(TTF->font, text, &TTF->w_px, &TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img,
		TTF_RenderText_Solid(TTF->font, text, gui_color("white")));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
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
