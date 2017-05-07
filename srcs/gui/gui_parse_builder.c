/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 06:34:17 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

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
		{
			gui_find_header(gui, fd, line);
			gui_free_array((void ***)&line, 0);
		}
		close(fd);
	}
	else
		gui_error(9);
}
