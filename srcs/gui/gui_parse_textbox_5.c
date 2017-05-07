/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_textbox_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

char	*gui_get_textbox_siz(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->size));
}

char	*gui_get_textbox_rfr(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_ftoa(tmp->refract_ind, 3));
}

char	*gui_get_textbox_rfl(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->reflect_k));
}
