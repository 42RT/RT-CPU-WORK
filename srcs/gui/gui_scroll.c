/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scroll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 17:32:04 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

t_button	*gui_scroll_button_init(void)
{
	t_button	*button;

	if (!(button = (t_button *)malloc(sizeof(t_button))))
		error(1);
	button->nature = BTN;
	button->action = "scroll";
	button->surface = NULL;
	button->bmp = NULL;
	return (button);
}

t_scroll	*gui_scroll_init(void)
{
	t_scroll	*scroll;

	if (!(scroll = (t_scroll *)malloc(sizeof(t_scroll))))
		error(1);
	if (!(scroll->tag = (char *)malloc(sizeof(char) * 3)))
		error(1);
	if (!(scroll->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	scroll->nature = SCL;
	scroll->surface = NULL;
	scroll->bmp = NULL;
	scroll->button = gui_scroll_button_init();
	return (scroll);
}

void		gui_scroll_value_free(char **value, int nb)
{
	int	i;

	i = nb - 1;
	while (i >= 0)
		value[i--] = NULL;
}

void		gui_scroll_set_halign(t_scroll *scroll)
{
	t_gui	*gui;

	gui = get_gui();
	if (scroll->dest.x == GUI_ALIGN_LEFT)
		scroll->dest.x = GUI_FONT_BORDER_STEP + 35;
	else if (scroll->dest.x == GUI_ALIGN_MID)
		scroll->dest.x = (GUI_WIDTH / 2) - (scroll->dest.w / 2) + 10;
	else if (scroll->dest.x == GUI_ALIGN_RIGHT)
		scroll->dest.x = GUI_WIDTH - scroll->dest.w - 50;
	else
		scroll->dest.x = scroll->dest.x;
}

void		gui_scroll_set(t_scroll *scroll, SDL_Rect dest)
{
	t_gui	*gui;

	gui = get_gui();
	scroll->dest.w = DEF->scl_w;
	scroll->dest.h = DEF->scl_h;
	scroll->dest.y += dest.y;
	gui_scroll_set_halign(scroll);
	scroll->button->dest.x = scroll->dest.x + scroll->dest.w;
	scroll->button->dest.y = scroll->dest.y;
	scroll->button->dest.w = DEF->scl_h;
	scroll->button->dest.h = DEF->scl_h;
}
