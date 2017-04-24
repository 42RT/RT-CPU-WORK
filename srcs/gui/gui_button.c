/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

t_button	*gui_button_init(void)
{
	t_button	*button;

	if (!(button = (t_button *)malloc(sizeof(t_button))))
		error(1);
	if (!(button->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	button->surface = NULL;
	button->bmp = NULL;
	button->nature = BTN;
	return (button);
}

void		gui_button_set_halign(t_button *button)
{
	t_gui	*gui;

	gui = get_gui();
	if (button->dest.x == GUI_ALIGN_LEFT)
		button->dest.x = 10;
	else if (button->dest.x == GUI_ALIGN_MID)
		button->dest.x = (GUI_WIDTH / 2) - (button->dest.w / 2);
	else if (button->dest.x == GUI_ALIGN_RIGHT)
		button->dest.x = GUI_WIDTH - (button->dest.w + 10);
	else
		button->dest.x = button->dest.x;
}

void		gui_button_set_valign(t_button *button)
{
	t_gui	*gui;

	gui = get_gui();
	if (button->dest.y == GUI_ALIGN_LEFT)
		button->dest.y = BLOCK[button->p]->dest.y;
	else if (button->dest.y == GUI_ALIGN_MID)
		button->dest.y = BLOCK[button->p]->dest.y
		+ (BLOCK[button->p]->dest.h / 7);
	else if (button->dest.y == GUI_ALIGN_RIGHT)
		button->dest.y = BLOCK[button->p]->dest.y + BLOCK[button->p]->dest.h
		- DEF->btn_h;
	else
		button->dest.y = button->dest.y;
}

void		gui_button_set(t_button *button)
{
	t_gui	*gui;

	gui = get_gui();
	button->dest.w = DEF->btn_w;
	button->dest.h = DEF->btn_h;
	gui_button_set_halign(button);
	gui_button_set_valign(button);
}
