/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_builder_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 06:50:55 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_parse_def_checkbox_suite(t_gui *gui, char **tmp)
{
	char	**tmp2;

	if (!ft_strcmp(tmp[0], "\ttexture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->cbx_texture = ft_strdup(tmp2[1]);
	}
	else if (!ft_strcmp(tmp[0], "\ttexture_selected"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->cbx_texture_selected = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_array((void ***)&tmp2, 2);
}

void	gui_parse_def_checkbox(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tsize"))
			DEF->cbx_size = ft_atoi(tmp[1]);
		else
			gui_parse_def_checkbox_suite(gui, tmp);
		gui_free_array((void ***)&tmp, 2);
	}
}

void	gui_parse_def_gauge_suite(t_gui *gui, char **tmp)
{
	char	**tmp2;

	if (!ft_strcmp(tmp[0], "\ttexture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->gau_texture = ft_strdup(tmp2[1]);
	}
	else if (!ft_strcmp(tmp[0], "\tcursor_texture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		DEF->gau_cursor_texture = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_array((void ***)&tmp2, 2);
}

void	gui_parse_def_gauge(t_gui *gui, int fd, int nb)
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
			DEF->gau_w = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\th"))
			DEF->gau_h = ft_atoi(tmp[1]);
		else
			gui_parse_def_gauge_suite(gui, tmp);
		gui_free_array((void ***)&tmp, 2);
	}
}
