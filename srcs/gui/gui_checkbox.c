/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_checkbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_reset_checkbox_state_suite(t_gui *gui, int id, int i)
{
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->checkbox == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->checkbox_qt)
			{
				gui_checkbox_get_state(CHECKBOX[i]);
				i++;
			}
			id++;
		}
	}
}

void		gui_reset_checkbox_state(t_gui *gui, char *target)
{
	int	i;

	if (!ft_strcmp(target, "PARAM") || !ft_strcmp(target, "ALL"))
	{
		i = 0;
		while (i < PARAM->checkbox_qt)
		{
			gui_checkbox_get_state(PARAM_CBX);
			i++;
		}
	}
	if (!ft_strcmp(target, "MAIN") || !ft_strcmp(target, "ALL"))
		gui_reset_checkbox_state_suite(gui, 0, 0);
}

t_checkbox	*gui_checkbox_init(void)
{
	t_checkbox	*checkbox;

	if ((checkbox = (t_checkbox *)malloc(sizeof(t_checkbox))) == NULL)
		error(1);
	if ((checkbox->txt = (t_txt *)malloc(sizeof(t_txt))) == NULL)
		error(1);
	checkbox->surface = NULL;
	checkbox->bmp = NULL;
	checkbox->nature = CBX;
	return (checkbox);
}

void		gui_checkbox_set_halign(t_checkbox *checkbox, SDL_Rect dest)
{
	if (checkbox->dest.x == GUI_ALIGN_LEFT)
		checkbox->dest.x = dest.x;
	else if (checkbox->dest.x == GUI_ALIGN_MID)
		checkbox->dest.x = (dest.w / 2) - (checkbox->dest.w / 2);
	else if (checkbox->dest.x == GUI_ALIGN_RIGHT)
		checkbox->dest.x = dest.w - checkbox->dest.w;
	else
		checkbox->dest.x = checkbox->dest.x;
}

void		gui_checkbox_set(t_checkbox *checkbox, SDL_Rect dest)
{
	t_gui	*gui;

	gui = get_gui();
	checkbox->dest.w = DEF->cbx_size;
	checkbox->dest.h = DEF->cbx_size;
	gui_checkbox_set_halign(checkbox, dest);
}
