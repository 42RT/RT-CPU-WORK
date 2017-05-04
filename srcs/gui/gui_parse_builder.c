/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

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
		else if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->cbx_texture = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\ttexture_selected"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->cbx_texture_selected = tmp[1];
		}
	}
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
		else if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->gau_texture = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\tcursor_texture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->gau_cursor_texture = tmp[1];
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

void	gui_find_header(t_gui *gui, int fd, char *line)
{
	if (!ft_strcmp(line, "WINDOW:"))
		gui_parse_window(gui, fd, 2);
	else if (!ft_strcmp(line, "PATH:"))
		gui_parse_path(gui, fd, 2);
	else if (!ft_strcmp(line, "DEFAULT_FONT:"))
		gui_parse_def_font(gui, fd, 3);
	else if (!ft_strcmp(line, "DEFAULT_TEXTBOX:"))
		gui_parse_def_textbox(gui, fd, 4);
	else if (!ft_strcmp(line, "DEFAULT_SCROLL:"))
		gui_parse_def_scroll(gui, fd, 7);
	else if (!ft_strcmp(line, "DEFAULT_BUTTON:"))
		gui_parse_def_button(gui, fd, 4);
	else if (!ft_strcmp(line, "DEFAULT_CHECKBOX:"))
		gui_parse_def_checkbox(gui, fd, 3);
	else if (!ft_strcmp(line, "DEFAULT_GAUGE:"))
		gui_parse_def_gauge(gui, fd, 4);
	else if (!ft_strcmp(line, "HELP MENU BUILDER:"))
		gui_parse_help_builder(gui, fd, 4);
	else if (!ft_strcmp(line, "PARAM MENU BUILDER:"))
		gui_parse_param_builder(gui, fd, 10);
	else if (!ft_strcmp(line, "MAIN BUILDER:"))
		gui_parse_main_builder(gui, fd, 10);
	else
		return ;
}

void	gui_parse_builder(t_gui *gui, char *file)
{
	int		fd;
	char	*line;
	int		ret;

	gui->action = 0;
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		while ((ret = get_next_line(fd, &line)) > 0)
			gui_find_header(gui, fd, line);
		close(fd);
	}
	else
		gui_error(9);
}
