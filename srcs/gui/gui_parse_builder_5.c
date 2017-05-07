/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_builder_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 10:42:44 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_parse_def_textbox_suite(t_gui *gui, char **tmp)
{
	char	**tmp2;

	if (!CMP(tmp[0], "\ttexture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->txb_texture = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\ttexture_selected"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->txb_texture_selected = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

void	gui_parse_def_textbox(t_gui *gui, int fd, int nb)
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
			DEF->txb_w = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\th"))
			DEF->txb_h = ft_atoi(tmp[1]);
		else
			gui_parse_def_textbox_suite(gui, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
}

void	gui_parse_def_scroll_suite(t_gui *gui, char **tmp)
{
	char	**tmp2;

	if (!CMP(tmp[0], "\tlist_texture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->scl_texture_list = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\tbutton_texture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->sclb_texture = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\tbutton_texture_selected"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->sclb_texture_selected = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\thead_texture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->scl_texture_head = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
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
		if (!CMP(tmp[0], "\tw"))
			DEF->scl_w = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\th"))
			DEF->scl_h = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\tmax_shown"))
			DEF->scl_max_shown = ft_atoi(tmp[1]);
		else
			gui_parse_def_scroll_suite(gui, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
}
