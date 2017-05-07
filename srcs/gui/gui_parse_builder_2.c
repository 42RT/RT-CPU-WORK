/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_builder_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 10:58:00 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_parse_window(t_gui *gui, int fd, int nb)
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
			gui->dest.w = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\th"))
			gui->dest.h = ft_atoi(tmp[1]);
		else
			gui_error(16);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
	gui->dest.x = 0;
	gui->dest.y = SDL_WINDOWPOS_CENTERED;
}

void	gui_parse_path_suite(t_gui *gui, char **tmp)
{
	char	**tmp2;

	if (!CMP(tmp[0], "\ttexture"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		PATH->texture = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\tfont"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		PATH->font = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

void	gui_parse_path(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		gui_parse_path_suite(gui, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
}

void	gui_parse_def_font_suite(t_gui *gui, char **tmp)
{
	char	**tmp2;

	if (!CMP(tmp[0], "\tfont"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		TTF->def_ttf = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

void	gui_parse_def_font(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!CMP(tmp[0], "\tsize"))
			TTF->def_size = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\tborder_step"))
			TTF->def_border_step = ft_atoi(tmp[1]);
		else
			gui_parse_def_font_suite(gui, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
}
