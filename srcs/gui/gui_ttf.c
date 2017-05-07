/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_ttf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:40:46 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:52:02 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_font_init(t_gui *gui, char *ttf, int size)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(PATH->font, ttf);
	path = ft_strjoin(tmp, ".ttf");
	gui_free_str(&tmp);
	TTF->font = TTF_OpenFont(path, size);
	gui_free_str(&path);
	if (TTF->font == NULL)
		gui_error(6);
	TTF_SizeText(TTF->font, "editor", NULL, &TTF->h_px);
}

void	gui_font_build(t_gui *gui)
{
	int	id;
	int	i;

	gui_font_init(gui, "Starjedi", TTF->def_size);
	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (CONTAINER->txt)
			gui_container_write_txt(CONTAINER, "white");
		i = 0;
		while (i < CONTAINER->button_qt)
			gui_widget_write_txt(BUTTON[i++], "white");
		i = 0;
		while (i < CONTAINER->scroll_qt)
			gui_widget_write_txt(SCROLL[i++], "white");
		i = 0;
		while (i < CONTAINER->textbox_qt)
			gui_widget_write_txt(TEXTBOX[i++], "white");
		i = 0;
		while (i < CONTAINER->checkbox_qt)
			gui_widget_write_txt(CHECKBOX[i++], "white");
		id++;
	}
	TTF_CloseFont(TTF->font);
}
