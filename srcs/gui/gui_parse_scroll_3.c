/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_scroll_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_get_16_9_10_suite(t_scroll *scroll, t_env *e)
{
	if (e->set->height == 2160)
		scroll->active_value = 8;
	else if (e->set->height == 1600)
		scroll->active_value = 7;
	else if (e->set->height == 1440)
		scroll->active_value = 6;
	else if (e->set->height == 1200)
		scroll->active_value = 5;
	else if (e->set->height == 1080)
		scroll->active_value = 4;
	else if (e->set->height == 1050)
		scroll->active_value = 3;
	else if (e->set->height == 720)
		scroll->active_value = 2;
	else if (e->set->height == 900)
		scroll->active_value = 1;
	else
		scroll->active_value = 0;
}

char	**gui_get_16_9_10(t_scroll *scroll, t_env *e)
{
	char	**value;

	scroll->nb_value = 9;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("1366x768");
	value[1] = ft_strdup("1440x900");
	value[2] = ft_strdup("1280x720");
	value[3] = ft_strdup("1680x1050");
	value[4] = ft_strdup("1920x1080");
	value[5] = ft_strdup("1920:1200");
	value[6] = ft_strdup("2560x1440");
	value[7] = ft_strdup("2560x1600");
	value[8] = ft_strdup("3840x2160");
	gui_get_16_9_10_suite(scroll, e);
	scroll->mod = 0;
	return (value);
}

void	gui_get_5_4_3_suite(t_scroll *scroll, t_env *e)
{
	if (e->set->height == 1536)
		scroll->active_value = 6;
	else if (e->set->height == 1200)
		scroll->active_value = 5;
	else if (e->set->height == 1050)
		scroll->active_value = 4;
	else if (e->set->height == 1024)
		scroll->active_value = 3;
	else if (e->set->height == 768)
		scroll->active_value = 2;
	else if (e->set->height == 600)
		scroll->active_value = 1;
	else
		scroll->active_value = 0;
}

char	**gui_get_5_4_3(t_scroll *scroll, t_env *e)
{
	char	**value;

	scroll->nb_value = 7;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("640x480");
	value[1] = ft_strdup("800x600");
	value[2] = ft_strdup("1024x768");
	value[3] = ft_strdup("1280x1024");
	value[4] = ft_strdup("1400x1050");
	value[5] = ft_strdup("1600x1200");
	value[6] = ft_strdup("2048x1536");
	gui_get_5_4_3_suite(scroll, e);
	scroll->mod = 0;
	return (value);
}

char	**gui_get_exotic_res(t_scroll *scroll, t_env *e)
{
	char	**value;

	scroll->nb_value = 3;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("42x42");
	value[1] = ft_strdup("1152x864");
	value[2] = ft_strdup("1600x1024");
	if (e->set->height == 1024)
		scroll->active_value = 2;
	else if (e->set->height == 864)
		scroll->active_value = 1;
	else
		scroll->active_value = 0;
	scroll->mod = 0;
	return (value);
}
