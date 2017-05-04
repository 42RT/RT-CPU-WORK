/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_main_container_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_container_info_suite(char **tmp, int id)
{
	t_gui	*gui;

	gui = get_gui();
	if (!ft_strcmp(tmp[0], "\th"))
		CONTAINER->dest.h = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\ttxt"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		CONTAINER->txt->content = tmp[1];
	}
	else if (!ft_strcmp(tmp[0], "\ttxt_anchor"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		CONTAINER->txt->anchor = tmp[1];
	}
	else if (!ft_strcmp(tmp[0], "\ttxt_align"))
		CONTAINER->txt->align = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tbutton_qt"))
		CONTAINER->button_qt = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tscroll_qt"))
		CONTAINER->scroll_qt = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\ttextbox_qt"))
		CONTAINER->textbox_qt = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tcheckbox_qt"))
		CONTAINER->checkbox_qt = ft_atoi(tmp[1]);
}

void		gui_parse_container_info(t_gui *gui, int fd, int id, int nb)
{
	char	**tmp;
	char	*line;
	int		i;

	i = 0;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tx"))
			CONTAINER->dest.x = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\ty"))
			CONTAINER->dest.y = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\tw"))
			CONTAINER->dest.w = ft_atoi(tmp[1]);
		else
			gui_parse_container_info_suite(tmp, id);
		gui_free_array((void **)tmp, 2);
		i++;
	}
	if (CONTAINER->txt->align == -1)
	{
		free(CONTAINER->txt);
		CONTAINER->txt = NULL;
	}
}

t_button	**gui_parse_container_button(int fd, int qt, int id)
{
	t_button	**button;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\tbutton:"))
		gui_error(12);
	if ((button = (t_button **)malloc(sizeof(t_button *) * qt)) == NULL)
		error(1);
	i = 0;
	while (i < qt)
	{
		button[i] = gui_parse_button(fd, 6);
		button[i]->p = id;
		button[i]->id = i;
		gui_button_set(button[i++]);
		if (i < qt)
		{
			get_next_line(fd, &line);
			if (ft_strcmp(line, "\t\t,"))
				gui_error(11);
		}
	}
	return (button);
}

t_scroll	**gui_parse_container_scroll(int fd, int qt, int id)
{
	t_scroll	**scroll;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\tscroll:"))
		gui_error(12);
	if (!(scroll = (t_scroll **)malloc(sizeof(t_scroll *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		scroll[i] = gui_parse_scroll(fd, 6);
		scroll[i]->p = id;
		scroll[i]->id = i;
		scroll[i]->value = gui_get_scroll_value(scroll[i]);
		gui_scroll_set(scroll[i++]);
		if (i < qt)
		{
			get_next_line(fd, &line);
			if (ft_strcmp(line, "\t\t,"))
				gui_error(11);
		}
	}
	return (scroll);
}
