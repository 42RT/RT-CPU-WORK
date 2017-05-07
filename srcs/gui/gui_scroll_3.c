/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scroll_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:59:37 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_reparse_scroll_value_suite(t_gui *gui, int ptid, int pti)
{
	int	id;
	int	i;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->scroll == NULL)
			id++;
		else
		{
			i = 0;
			while ((id == 0 && i == 0) || (id == ptid && i == pti))
				i++;
			while (i < BLOCK[id]->scroll_qt)
			{
				gui_free_carray(&(SCROLL[i]->value), SCROLL[i]->nb_value);
				SCROLL[i]->active_value = 0;
				SCROLL[i]->value = gui_get_scroll_value(SCROLL[i]);
				i++;
			}
			id++;
		}
	}
}

void	gui_reparse_scroll_value(t_gui *gui, char *target, int ptid, int pti)
{
	int	i;

	if (!ft_strcmp(target, "PARAM") || !ft_strcmp(target, "ALL"))
	{
		i = 1;
		while (i < PARAM->scroll_qt)
		{
			gui_free_carray(&(PARAM_SCL->value), PARAM_SCL->nb_value);
			PARAM_SCL->active_value = 0;
			PARAM_SCL->value = gui_get_scroll_value(PARAM_SCL);
			i++;
		}
	}
	if (!ft_strcmp(target, "MAIN") || !ft_strcmp(target, "ALL"))
		gui_reparse_scroll_value_suite(gui, ptid, pti);
}
