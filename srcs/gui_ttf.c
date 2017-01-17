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

SDL_Color	gui_build_font_color()
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
	TTF->font = TTF_OpenFont(DEF_RESS_PATH""DEF_FONT_FILE, DEF_FONT_SIZE);
	TTF_SizeText(TTF->font, "EDITOR", NULL, &TTF->h_px);
	TTF->h_px += 10;
	TTF_CloseFont(TTF->font);
}

void	gui_write(char *text, t_container *container, int x, int y)
{
	t_gui	*gui;

	gui = get_gui();
	TTF->font = TTF_OpenFont(DEF_RESS_PATH""DEF_FONT_FILE, DEF_FONT_SIZE);
	TTF_SizeText(TTF->font, text, &TTF->w_px, NULL);
	if (TTF->font == NULL)
		gui_error(6);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img, 
			TTF_RenderText_Blended(TTF->font, text, gui_build_font_color()));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	if (x == 0)
		TTF->rect.x = DEF_FONT_BORDER_STEP;
	else if (x == 1)
		TTF->rect.x = (DEF_GUI_WIDTH / 2) - (TTF->w_px / 2);
	else if (x == 2)
		TTF->rect.x = DEF_GUI_WIDTH - TTF->w_px - DEF_FONT_BORDER_STEP;
	else
		TTF->rect.x = x;
	TTF->rect.y = y + container->up_lim;
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
}

void	gui_build_font(t_gui *gui)
{
	int h_step;
	
	gui_font_get_px(gui);
	gui_write("SCENE", BLOCK[0], DEF_FONT_ALIGN_LEFT, 15);
	gui_write("OBJECT", BLOCK[0], DEF_FONT_ALIGN_LEFT, 45);
	h_step = BLOCK[1]->px / 5;
	gui_write("Position :", BLOCK[1], DEF_FONT_ALIGN_LEFT, h_step - TTF->h_px);
	gui_write("X", BLOCK[1], DEF_FONT_ALIGN_LEFT, h_step);
	gui_write("Y", BLOCK[1], DEF_FONT_ALIGN_MID, h_step);
	gui_write("Z", BLOCK[1], DEF_FONT_ALIGN_LEFT, h_step + TTF->h_px);
	h_step *= 3;
	gui_write("Angle :", BLOCK[1], DEF_FONT_ALIGN_LEFT, h_step);
	gui_write("V", BLOCK[1], DEF_FONT_ALIGN_LEFT, h_step + TTF->h_px);
	gui_write("H", BLOCK[1], DEF_FONT_ALIGN_MID, h_step + TTF->h_px);
	h_step = BLOCK[2]->px / 10;
	gui_write("COLOR :", BLOCK[2], DEF_FONT_ALIGN_LEFT, h_step - TTF->h_px);
	gui_write("R", BLOCK[2], DEF_FONT_ALIGN_LEFT, h_step);
	gui_write("G", BLOCK[2], DEF_FONT_ALIGN_MID, h_step);
	gui_write("B", BLOCK[2], DEF_FONT_ALIGN_LEFT, h_step + TTF->h_px);
	gui_write("A", BLOCK[2], DEF_FONT_ALIGN_MID, h_step + TTF->h_px);
	h_step *= 3;
	gui_write("Reflection", BLOCK[2], DEF_FONT_ALIGN_LEFT, h_step);
	gui_write("Refraction", BLOCK[2], DEF_FONT_ALIGN_LEFT, h_step * 2);
	gui_write("Material", BLOCK[2], DEF_FONT_ALIGN_LEFT, h_step * 3);
	h_step = BLOCK[3]->px / 5;
	gui_write("Texture :", BLOCK[3], DEF_FONT_ALIGN_LEFT, 15);
	gui_write("P", BLOCK[3], DEF_FONT_ALIGN_LEFT, 45);
	gui_write("N", BLOCK[3], DEF_FONT_ALIGN_MID, 45);
	gui_write("APPLY", BLOCK[4], DEF_FONT_ALIGN_LEFT, 10);
	gui_write("DEL", BLOCK[4], DEF_FONT_ALIGN_MID, 10);
	gui_write("SAVE", BLOCK[4], DEF_FONT_ALIGN_RIGHT, 10);
	gui_write("APPLY", BLOCK[5], DEF_FONT_ALIGN_LEFT, 10);
	gui_write("APPLY", BLOCK[5], DEF_FONT_ALIGN_MID, 10);
	gui_write("APPLY", BLOCK[5], DEF_FONT_ALIGN_RIGHT, 10);
	TTF_CloseFont(TTF->font);
}
