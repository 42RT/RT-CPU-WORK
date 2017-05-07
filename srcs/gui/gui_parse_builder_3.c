/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_builder_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 05:58:26 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_parse_def_scroll_suite(t_gui *gui, char **tmp)
{
	if (!ft_strcmp(tmp[0], "\tlist_texture"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		DEF->scl_texture_list = tmp[1];
	}
	else if (!ft_strcmp(tmp[0], "\tbutton_texture"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		DEF->sclb_texture = tmp[1];
	}
	else if (!ft_strcmp(tmp[0], "\tbutton_texture_selected"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		DEF->sclb_texture_selected = tmp[1];
	}
}

void	gui_parse_def_scroll(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tw"))
			DEF->scl_w = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\th"))
			DEF->scl_h = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\tmax_shown"))
			DEF->scl_max_shown = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\thead_texture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->scl_texture_head = tmp[1];
		}
		else
			gui_parse_def_scroll_suite(gui, tmp);
		free(tmp);
	}
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
		if (!ft_strcmp(tmp[0], "\tw"))
			DEF->btn_w = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\th"))
			DEF->btn_h = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->btn_texture = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\ttexture_selected"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->btn_texture_selected = tmp[1];
		}
		free(tmp);
	}
}

void	gui_parse_help_builder(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	if (!(HELP = (t_help *)malloc(sizeof(t_help))))
		error(1);
	HELP->nature = HLP;
	HELP->active = 0;
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
		free(tmp);
	}
}

