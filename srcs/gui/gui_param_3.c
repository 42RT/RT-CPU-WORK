/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_param_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 17:32:04 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_param_text_build_suite(t_gui *gui)
{
	int		i;
	char	*tmp;

	i = 0;
	while (PARAM->gauge_qt > i++)
	{
		gui_widget_write_txt(PARAM_GAU, "white");
		PARAM_GAU->txt->align = 315;
		tmp = ft_strdup(PARAM_GAU->txt->content);
		free(PARAM_GAU->txt->content);
		gui_gauge_convert_value(PARAM_GAU);
		gui_widget_write_txt(PARAM_GAU, "white");
		free(PARAM_GAU->txt->content);
		PARAM_GAU->txt->content = ft_strdup(tmp);
		free(tmp);
		PARAM_GAU->txt->align = GUI_ALIGN_LEFT;
	}
	i = 0;
	while (PARAM->freetxt_qt > i++)
		gui_freetxt_write(PARAM_FTT, "white");
	TTF_CloseFont(TTF->font);
}

void	gui_param_text_build(t_gui *gui)
{
	int	i;

	gui_font_init(gui, "Audiowide-Regular", GUI_FONT_SIZE + 1);
	i = 0;
	while (PARAM->button_qt > i++)
		gui_widget_write_txt(PARAM_BTN, "white");
	i = 0;
	while (PARAM->scroll_qt > i++)
		gui_widget_write_txt(PARAM_SCL, "white");
	i = 0;
	while (PARAM->textbox_qt > i++)
		gui_widget_write_txt(PARAM_TXB, "white");
	i = 0;
	while (PARAM->checkbox_qt > i++)
		gui_widget_write_txt(PARAM_CBX, "white");
	gui_param_text_build_suite(gui);
}
