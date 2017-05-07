/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_param_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 05:47:14 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_param_text_build_suite(t_gui *gui)
{
	int		i;
	char	*tmp;

	i = 0;
	while (PARAM->gauge_qt > i)
	{
		gui_widget_write_txt(PARAM_GAU, "white");
		PARAM_GAU->txt->align = 315;
		tmp = ft_strdup(PARAM_GAU->txt->content);
		gui_free_array((void ***)&PARAM_GAU->txt->content, 0);
		gui_gauge_convert_value(PARAM_GAU);
		gui_widget_write_txt(PARAM_GAU, "white");
		gui_free_array((void ***)&PARAM_GAU->txt->content, 0);
		PARAM_GAU->txt->content = ft_strdup(tmp);
		gui_free_array((void ***)&tmp, 0);
		PARAM_GAU->txt->align = GUI_ALIGN_LEFT;
		i++;
	}
	i = 0;
	while (PARAM->freetxt_qt > i)
		gui_freetxt_write(PARAM->freetxt[i++], "white");
}

void	gui_param_text_build(t_gui *gui)
{
	int	i;

	gui_font_init(gui, "Audiowide-Regular", GUI_FONT_SIZE + 1);
	i = 0;
	while (PARAM->button_qt > i)
		gui_widget_write_txt(PARAM->button[i++], "white");
	i = 0;
	while (PARAM->scroll_qt > i)
		gui_widget_write_txt(PARAM->scroll[i++], "white");
	i = 0;
	while (PARAM->textbox_qt > i)
		gui_widget_write_txt(PARAM->textbox[i++], "white");
	i = 0;
	while (PARAM->checkbox_qt > i)
		gui_widget_write_txt(PARAM->checkbox[i++], "white");
	gui_param_text_build_suite(gui);
	TTF_CloseFont(TTF->font);
}
