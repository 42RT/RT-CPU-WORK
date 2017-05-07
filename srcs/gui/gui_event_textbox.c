/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_textbox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 10:52:39 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	event_txb_edit(t_gui *gui, t_textbox *textbox, char *color)
{
	gui_font_init(gui, "Starjedi", 16);
	gui_write_textbox_value(gui, textbox, color);
	TTF_CloseFont(TTF->font);
}

void	event_txb_value_force(t_textbox *textbox, char *forced_value)
{
	int	i;
	int	j;

	i = textbox->maxlen - 1;
	j = ft_strlen(forced_value) - 1;
	while (j >= 0)
	{
		textbox->value[i] = forced_value[j];
		i--;
		j--;
	}
	while (i >= 0)
		textbox->value[i--] = ' ';
}

void	event_txb_value_allowed(t_textbox *textbox)
{
	char	*tmp;

	if (ft_atoi(textbox->value) > textbox->max)
	{
		tmp = ft_itoa(textbox->max);
		event_txb_value_force(textbox, tmp);
		gui_free_str(&tmp);
	}
	else if (ft_atoi(textbox->value) < textbox->min)
	{
		tmp = ft_itoa(textbox->min);
		event_txb_value_force(textbox, tmp);
		gui_free_str(&tmp);
	}
	else
		return ;
}

void	event_txb_deselect(t_gui *gui)
{
	t_textbox	*tmp;

	tmp = gui->widget_active;
	tmp->edited = 0;
	gui->widget_active = NULL;
	gui_widget_texture_get_bmp(tmp, "textbox_white.bmp");
	gui_widget_display(tmp);
	gui_widget_draw_in_line(tmp->dest, 1, "black");
	event_txb_value_allowed(tmp);
	event_txb_edit(gui, tmp, "black");
	tmp = NULL;
}

void	event_txb_select(t_gui *gui, t_textbox *textbox)
{
	if (textbox == gui->widget_active)
		event_widget_deselect(gui);
	else
	{
		if (gui->widget_active)
			event_widget_deselect(gui);
		gui->widget_active = textbox;
		gui_widget_texture_get_bmp(textbox, "textbox_black.bmp");
		gui_widget_display(textbox);
		gui_widget_draw_in_line(textbox->dest, 1, "white");
		textbox->vlen = 0;
		event_txb_edit(gui, gui->widget_active, "white");
	}
}
