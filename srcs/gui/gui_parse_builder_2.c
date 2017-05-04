/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_builder_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
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
		if (!ft_strcmp(tmp[0], "\tw"))
			gui->dest.w = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\th"))
			gui->dest.h = ft_atoi(tmp[1]);
		free(tmp);
	}
	gui->dest.x = 0;
	gui->dest.y = SDL_WINDOWPOS_CENTERED;
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
		if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			PATH->texture = ft_strdup(tmp[1]);
		}
		else if (!ft_strcmp(tmp[0], "\tfont"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			PATH->font = ft_strdup(tmp[1]);
		}
		free(tmp);
	}
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
		if (!ft_strcmp(tmp[0], "\tsize"))
			TTF->def_size = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\tfont"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			TTF->def_ttf = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\tborder_step"))
			TTF->def_border_step = ft_atoi(tmp[1]);
		free(tmp);
	}
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
		if (!ft_strcmp(tmp[0], "\tw"))
			DEF->txb_w = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\th"))
			DEF->txb_h = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->txb_texture = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\ttexture_selected"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->txb_texture_selected = tmp[1];
		}
		free(tmp);
	}
}
