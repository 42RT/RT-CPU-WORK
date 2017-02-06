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

SDL_Color	gui_color_data_set(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

SDL_Color	gui_color(char *choice)
{
	if (ft_strstr(choice, "white"))
		return (gui_color_data_set(255, 255, 255, 255));
	if (ft_strstr(choice, "black"))
		return (gui_color_data_set(0, 0, 0, 255));
	if (ft_strstr(choice, "red brick"))
		return (gui_color_data_set(130, 5, 5, 255));
	if (ft_strstr(choice, "red"))
		return (gui_color_data_set(255, 0, 0, 255));
	if (ft_strstr(choice, "purple deep"))
		return (gui_color_data_set(31, 17, 70, 255));
	if (ft_strstr(choice, "teal"))
		return (gui_color_data_set(43, 202, 189, 255));
	else
		return (gui_color_data_set(0, 0, 0, 0));
}

void	gui_font_init(t_gui *gui, char *ttf, int size)
{
	char *path;

	path = ft_strjoin(PATH->font, ttf);
	path = ft_strjoin(path, ".ttf");
	TTF->font = TTF_OpenFont(path, size);
	if (TTF->font == NULL)
		gui_error(6);
	TTF_SizeText(TTF->font, "editor", NULL, &TTF->h_px);
}

void	gui_container_write_txt(void *widget, char *color)
{
	int		cX;
	t_gui	*gui;

	gui = get_gui();
	if (((REF *)widget)->p > -1)
		cX = BLOCK[((REF *)widget)->p]->dest.x;
	else if (((REF *)widget)->nature == PRM)
		cX = PARAM->dest.x;
	else
		cX = HELP->dest.x;
	TTF_SizeText(TTF->font, ((REF *)widget)->txt->content, &TTF->w_px, &TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img, 
		TTF_RenderText_Solid(TTF->font, ((REF *)widget)->txt->content,
			gui_color(color)));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	if (((REF *)widget)->txt->align == GUI_ALIGN_LEFT)
		TTF->rect.x = cX + GUI_FONT_BORDER_STEP;
	else if (((REF *)widget)->txt->align == GUI_ALIGN_MID)
		TTF->rect.x = cX + (GUI_WIDTH / 2) - (TTF->w_px / 2);
	else if (((REF *)widget)->txt->align == GUI_ALIGN_RIGHT)
		TTF->rect.x = cX + GUI_WIDTH - TTF->w_px - GUI_FONT_BORDER_STEP;
	else
		TTF->rect.x = cX + ((REF *)widget)->dest.x;
	TTF->rect.y = ((REF *)widget)->dest.y + ((((REF *)widget)->dest.h -
		TTF->h_px - 4) / 2);
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	SDL_DestroyTexture(TTF->texture);
}

void	gui_widget_write_txt(void *widget, char *color)
{
	t_gui	*gui;

	gui = get_gui();
	if (!ft_strcmp(((REF *)widget)->txt->anchor, "this"))
	{
		TTF_SizeText(TTF->font, ((REF *)widget)->txt->content, &TTF->w_px, &TTF->h_px);
		TTF->texture = SDL_CreateTextureFromSurface(gui->img, 
			TTF_RenderText_Solid(TTF->font, ((REF *)widget)->txt->content,
				gui_color(color)));
		SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
		if (((REF *)widget)->txt->align == GUI_ALIGN_LEFT)
			TTF->rect.x = ((REF *)widget)->dest.x - TTF->w_px - GUI_FONT_BORDER_STEP;
		else if (((REF *)widget)->txt->align == GUI_ALIGN_MID)
			TTF->rect.x = ((REF *)widget)->dest.x + ((((REF *)widget)->dest.w - TTF->w_px) / 2);
		else if (((REF *)widget)->txt->align == GUI_ALIGN_RIGHT)
			TTF->rect.x = GUI_WIDTH - TTF->w_px - GUI_FONT_BORDER_STEP;
		else
			TTF->rect.x = ((REF *)widget)->dest.x;
		TTF->rect.y = ((REF *)widget)->dest.y + ((((REF *)widget)->dest.h -
			TTF->h_px - 4) / 2);
		SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
		SDL_DestroyTexture(TTF->texture);
	}
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
	gui_anti_aliasing_set(TTF->rect.x, TTF->rect.y, TTF->w_px, TTF->h_px);
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
	gui_anti_aliasing_set(TTF->rect.x, TTF->rect.y, TTF->w_px, TTF->h_px);
	SDL_DestroyTexture(TTF->texture);
}

void	gui_font_build(t_gui *gui)
{
	int	id;
	int	i;

	gui_font_init(gui, "Starjedi", TTF->def_size);
	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (CONTAINER->button_qt > 0)
		{
			i = 0;
			while (i < CONTAINER->button_qt)
			{
				gui_widget_write_txt(BUTTON[i], "white");
				i++;
			}
		}
		if (CONTAINER->scroll_qt > 0)
		{
			i = 0;
			while (i < CONTAINER->scroll_qt)
			{
				gui_widget_write_txt(SCROLL[i], "white");
				i++;
			}
		}
		if (CONTAINER->textbox_qt > 0)
		{
			i = 0;
			while (i < CONTAINER->textbox_qt)
			{
				gui_widget_write_txt(TEXTBOX[i], "white");
				i++;
			}
		}
		if (CONTAINER->checkbox_qt > 0)
		{
			i = 0;
			while (i < CONTAINER->checkbox_qt)
			{
				gui_widget_write_txt(CHECKBOX[i], "white");
				i++;
			}
		}
		id++;
	}
	TTF_CloseFont(TTF->font);
}
