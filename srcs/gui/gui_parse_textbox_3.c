/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_textbox_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

char	*gui_get_textbox_az(void)
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
	return (ft_itoa(tmp->ang.z / M_PI_2 * 90));
}

char	*gui_get_textbox_r(void)
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
	return (ft_itoa(tmp->color.r));
}

char	*gui_get_textbox_g(void)
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
	return (ft_itoa(tmp->color.g));
}

char	*gui_get_textbox_b(void)
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
	return (ft_itoa(tmp->color.b));
}

char	*gui_get_textbox_a(void)
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
	return (ft_itoa(tmp->transparency));
}
