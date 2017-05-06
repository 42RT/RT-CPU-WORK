/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_textbox_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

char	*gui_get_textbox_x(void)
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
	return (ft_itoa(tmp->pos.x));
}

char	*gui_get_textbox_y(void)
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
	return (ft_itoa(tmp->pos.y));
}

char	*gui_get_textbox_z(void)
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
	return (ft_itoa(tmp->pos.z));
}

char	*gui_get_textbox_ax(void)
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
	return (ft_itoa(tmp->ang.x / M_PI_2 * 90));
}

char	*gui_get_textbox_ay(void)
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
	return (ft_itoa(tmp->ang.y / M_PI_2 * 90));
}
