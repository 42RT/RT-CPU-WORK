/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_param_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 06:50:58 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_param_get_bmp_n_display(t_gui *gui)
{
	gui_widget_texture_get_bmp(PARAM, "help_black.bmp");
	SDL_SetTextureBlendMode(PARAM->bmp, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(PARAM->bmp, 240);
	gui_widget_display(PARAM);
	gui_widget_draw_outline(PARAM->dest, 5, "purple deep");
	SDL_RenderPresent(gui->img);
}

void	gui_param_scroll_create_all(t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->scroll_qt)
	{
		gui_widget_texture_get_bmp(PARAM_SCL, "textbox_white.bmp");
		gui_widget_display(PARAM_SCL);
		gui_widget_draw_in_line(PARAM_SCL->dest, 1, "black");
		gui_scroll_value_write(gui, PARAM_SCL, "black");
		gui_widget_texture_get_bmp(PARAM_SCL_B, "scrollB_jade.bmp");
		gui_widget_display(PARAM_SCL_B);
		gui_widget_draw_in_line(PARAM_SCL_B->dest, 1, "black");
		i++;
	}
}

void	gui_param_textbox_create_all(t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->textbox_qt)
	{
		if (WIDGET == PARAM_TXB)
			gui_widget_texture_get_bmp(PARAM_TXB, "textbox_black.bmp");
		else
			gui_widget_texture_get_bmp(PARAM_TXB, "textbox_white.bmp");
		gui_widget_display(PARAM_TXB);
		gui_widget_draw_in_line(PARAM_TXB->dest, 1, "black");
		event_txb_edit(gui, PARAM_TXB, "black");
		i++;
	}
}

void	gui_param_gauge_create_all(t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->gauge_qt)
	{
		gui_widget_texture_get_bmp(PARAM_GAU, DEF->gau_texture);
		gui_widget_display(PARAM_GAU);
		gui_widget_texture_get_bmp(PARAM_GAU_C, DEF->gau_cursor_texture);
		gui_widget_display(PARAM_GAU_C);
		i++;
	}
}

void	gui_param_checkbox_create_all(t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->checkbox_qt)
	{
		if (PARAM_CBX->selected == 1)
		{
			gui_widget_texture_get_bmp(PARAM_CBX, "checkbox_selected.bmp");
			gui_widget_display(PARAM_CBX);
			gui_widget_draw_in_line(PARAM_CBX->dest, 3, "teal");
			gui_widget_draw_in_line(PARAM_CBX->dest, 1, "black");
		}
		else
		{
			gui_widget_texture_get_bmp(PARAM_CBX, "textbox_white.bmp");
			gui_widget_display(PARAM_CBX);
			gui_widget_draw_in_line(PARAM_CBX->dest, 1, "black");
		}
		i++;
	}
}
