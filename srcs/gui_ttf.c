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
	TTF->font = TTF_OpenFont(GUI_RESS_PATH""GUI_FONT_FILE, GUI_FONT_SIZE);
	TTF_SizeText(TTF->font, "EDITOR", NULL, &TTF->h_px);
	TTF->h_px += 10;
}

void	gui_write_container(char *text, t_container *container, int x, int y)
{
	t_gui	*gui;

	gui = get_gui();
	if (TTF->font == NULL)
		gui_error(6);
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
	if (TTF->font == NULL)
		gui_error(6);
	TTF_SizeText(TTF->font, text, &TTF->w_px, &TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img,
		TTF_RenderText_Blended(TTF->font, text, gui_font_color_select()));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	TTF->rect.x = button->dest.x + ((button->dest.w - TTF->w_px) / 2);
	TTF->rect.y = button->dest.y + ((button->dest.h - TTF->h_px) / 2);
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
}

void	gui_font_build(t_gui *gui)
{
	int h_step;
	
	gui_font_get_px(gui);
	gui_write_container("SCENE", BLOCK[0], GUI_ALIGN_LEFT, 15);
	gui_write_container("OBJECT", BLOCK[0], GUI_ALIGN_LEFT, 45);
	h_step = BLOCK[1]->px / 5;
	gui_write_container("Position :", BLOCK[1], GUI_ALIGN_LEFT, h_step - TTF->h_px);
	gui_write_container("X", BLOCK[1], GUI_ALIGN_LEFT, h_step);
	gui_write_container("Y", BLOCK[1], GUI_ALIGN_MID, h_step);
	gui_write_container("Z", BLOCK[1], GUI_ALIGN_LEFT, h_step + TTF->h_px);
	h_step *= 3;
	gui_write_container("Angle :", BLOCK[1], GUI_ALIGN_LEFT, h_step);
	gui_write_container("V", BLOCK[1], GUI_ALIGN_LEFT, h_step + TTF->h_px);
	gui_write_container("H", BLOCK[1], GUI_ALIGN_MID, h_step + TTF->h_px);
	h_step = BLOCK[2]->px / 10;
	gui_write_container("COLOR :", BLOCK[2], GUI_ALIGN_LEFT, h_step - TTF->h_px);
	gui_write_container("R", BLOCK[2], GUI_ALIGN_LEFT, h_step);
	gui_write_container("G", BLOCK[2], GUI_ALIGN_MID, h_step);
	gui_write_container("B", BLOCK[2], GUI_ALIGN_LEFT, h_step + TTF->h_px);
	gui_write_container("A", BLOCK[2], GUI_ALIGN_MID, h_step + TTF->h_px);
	h_step *= 3;
	gui_write_container("Reflection", BLOCK[2], GUI_ALIGN_LEFT, h_step);
	gui_write_container("Refraction", BLOCK[2], GUI_ALIGN_LEFT, h_step * 2);
	gui_write_container("Material", BLOCK[2], GUI_ALIGN_LEFT, h_step * 3);
	h_step = BLOCK[3]->px / 5;
	gui_write_container("Texture :", BLOCK[3], GUI_ALIGN_LEFT, 15);
	gui_write_container("P", BLOCK[3], GUI_ALIGN_LEFT, 45);
	gui_write_container("N", BLOCK[3], GUI_ALIGN_MID, 45);
	gui_write_button("DEL", BLOCK[4]->button[0]);
	gui_write_button("SAVE", BLOCK[4]->button[1]);
	gui_write_button("APPLY", BLOCK[4]->button[2]);
	gui_write_button("PARAM", BLOCK[5]->button[0]);
	gui_write_button("HELP", BLOCK[5]->button[1]);
	gui_write_button("EXIT", BLOCK[5]->button[2]);
	TTF_CloseFont(TTF->font);
}
