/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_builder_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 10:41:07 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_parse_def_button_suite(t_gui *gui, char **tmp)
{
	char	**tmp2;

	if (!ft_strcmp(tmp[0], "\ttexture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->btn_texture = ft_strdup(tmp2[1]);
	}
	else if (!ft_strcmp(tmp[0], "\ttexture_selected"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->btn_texture_selected = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

void	gui_parse_def_button(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!CMP(tmp[0], "\tw"))
			DEF->btn_w = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\th"))
			DEF->btn_h = ft_atoi(tmp[1]);
		else
			gui_parse_def_button_suite(gui, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
}

void	gui_init_help(t_gui *gui)
{
	if (!(HELP = (t_help *)malloc(sizeof(t_help))))
		error(1);
	HELP->nature = HLP;
	HELP->active = 0;
}

void	gui_parse_help_builder(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	gui_init_help(gui);
	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tx"))
			HELP->dest.x = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\ty"))
			HELP->dest.y = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\tw"))
			HELP->dest.w = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\th"))
			HELP->dest.h = ft_atoi(tmp[1]);
		else
			gui_error(16);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
}
