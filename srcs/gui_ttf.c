/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_ttf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:40:46 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:22 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

SDL_Color	gui_font_color_select()
{
	SDL_Color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	return (color);
}

void	gui_font_get_px(t_gui *gui)
{
	TTF->font = TTF_OpenFont(GUI_FONT_PATH""GUI_FONT_FILE".ttf", GUI_FONT_SIZE);
	if (TTF->font == NULL)
		gui_error(6);
	TTF_SizeText(TTF->font, "editor", NULL, &TTF->h_px);
	TTF->h_px += 10;
}

void	gui_write_container(char *text, t_container *container, int x, int y)
{
	t_gui	*gui;

	gui = get_gui();
	TTF_SizeText(TTF->font, text, &TTF->w_px, NULL);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img, 
			TTF_RenderText_Blended(TTF->font, text, gui_font_color_select()));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	if (x == GUI_ALIGN_LEFT)
		TTF->rect.x = GUI_FONT_BORDER_STEP;
	else if (x == GUI_ALIGN_MID)
		TTF->rect.x = (GUI_WIDTH / 2) - (TTF->w_px / 2);
	else if (x == GUI_ALIGN_RIGHT)
		TTF->rect.x = GUI_WIDTH - TTF->w_px - GUI_FONT_BORDER_STEP;
	else
		TTF->rect.x = x;
	TTF->rect.y = y + container->up_lim;
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
}

void	gui_write_button(char *text, t_button *button)
{
	t_gui *gui;

	gui = get_gui();
	TTF_SizeText(TTF->font, text, &TTF->w_px, &TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img,
		TTF_RenderText_Blended(TTF->font, text, gui_font_color_select()));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	TTF->rect.x = button->dest.x + ((button->dest.w - TTF->w_px) / 2);
	TTF->rect.y = button->dest.y + ((button->dest.h - TTF->h_px - 4) / 2);
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
}

void	gui_write_textbox_tag(char *text, t_textbox *textbox, int align)
{
	t_gui *gui;

	gui = get_gui();
	TTF_SizeText(TTF->font, text, &TTF->w_px, &TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img,
		TTF_RenderText_Blended(TTF->font, text, gui_font_color_select()));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	if (align == GUI_ALIGN_LEFT)
		TTF->rect.x = textbox->dest.x - TTF->w_px - GUI_FONT_BORDER_STEP;
	else
		TTF->rect.x = align;
	TTF->rect.y = textbox->dest.y + ((textbox->dest.h - TTF->h_px) / 2);
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
}

void	gui_font_build(t_gui *gui)
{
	
	gui_font_get_px(gui);
	gui_write_container("scene", BLOCK[0], GUI_ALIGN_LEFT, 10);
	gui_write_container("object", BLOCK[0], GUI_ALIGN_LEFT, 40);
	gui_write_container("position :", BLOCK[1], GUI_ALIGN_LEFT, 10);
	gui_write_textbox_tag("x", BLOCK[1]->textbox[0], GUI_ALIGN_LEFT);
	gui_write_textbox_tag("y", BLOCK[1]->textbox[1], GUI_ALIGN_LEFT);
	gui_write_textbox_tag("z", BLOCK[1]->textbox[2], GUI_ALIGN_LEFT);
	gui_write_container("angle :", BLOCK[2], GUI_ALIGN_LEFT, 10);
	gui_write_textbox_tag("v", BLOCK[2]->textbox[0], GUI_ALIGN_LEFT);
	gui_write_textbox_tag("h", BLOCK[2]->textbox[1], GUI_ALIGN_LEFT);
	gui_write_container("color :", BLOCK[3], GUI_ALIGN_LEFT, 10);
	gui_write_textbox_tag("r", BLOCK[3]->textbox[0], GUI_ALIGN_LEFT);
	gui_write_textbox_tag("g", BLOCK[3]->textbox[1], GUI_ALIGN_LEFT);
	gui_write_textbox_tag("b", BLOCK[3]->textbox[2], GUI_ALIGN_LEFT);
	gui_write_textbox_tag("a", BLOCK[3]->textbox[3], GUI_ALIGN_LEFT);
	gui_write_textbox_tag("reflection", BLOCK[4]->textbox[0], GUI_FONT_BORDER_STEP);
	gui_write_textbox_tag("refraction", BLOCK[5]->textbox[0], GUI_FONT_BORDER_STEP);
	gui_write_container("material", BLOCK[6], GUI_ALIGN_LEFT, 5);
	gui_write_container("texture :", BLOCK[7], GUI_ALIGN_LEFT, 5);
	gui_write_container("p", BLOCK[7], GUI_ALIGN_LEFT, 45);
	gui_write_container("n", BLOCK[7], GUI_ALIGN_MID, 45);
	gui_write_button("del", BLOCK[8]->button[0]);
	gui_write_button("save", BLOCK[8]->button[1]);
	gui_write_button("apply", BLOCK[8]->button[2]);
	gui_write_button("param", BLOCK[9]->button[0]);
	gui_write_button("help", BLOCK[9]->button[1]);
	gui_write_button("exit", BLOCK[9]->button[2]);
	TTF_CloseFont(TTF->font);
}
