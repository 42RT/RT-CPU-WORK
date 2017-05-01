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

void	gui_container_write_txt_suite(void *widget, int cx)
{
	t_gui	*gui;

	gui = get_gui();
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
	gui_txt_to_texture(((REF *)widget)->txt->content, "SOLID", color);
	gui_container_write_txt_suite(widget, cx);
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
}

void	gui_widget_write_anchored_txt(t_gui *gui, void *widget, char *color)
{
	gui_txt_to_texture(((REF *)widget)->txt->content, "SOLID", color);
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

void	gui_scroll_value_write(t_gui *gui, t_scroll *scroll, char *color)
{
	gui_font_init(gui, "Starjedi", 16);
	if (!ft_strcmp(scroll->tag, "SCN") && scroll->active_value == -1)
		gui_txt_to_texture("default", "SOLID", color);
	else
		gui_txt_to_texture(scroll->value[scroll->active_value], "SOLID", color);
	TTF->rect.x = scroll->dest.x + 5;
	TTF->rect.y = scroll->dest.y - 4;
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
	TTF_CloseFont(TTF->font);
}
