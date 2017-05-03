/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_main_container.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_cnt_txb_suite(t_textbox **txb, int fd, int qt, int id)
{
	t_gui	*gui;
	int		i;
	char	*line;

	gui = get_gui();
	i = 0;
	while (i < qt)
	{
		txb[i] = gui_parse_textbox(fd, 8);
		txb[i]->p = id;
		txb[i]->id = i;
		gui_get_textbox_value(txb[i]);
		gui_textbox_set(txb[i], gui->dest);
		i++;
		if (i < qt)
		{
			get_next_line(fd, &line);
			if (ft_strcmp(line, "\t\t,"))
				gui_error(11);
		}
	}
}

t_textbox	**gui_parse_container_textbox(int fd, int qt, int id)
{
	t_textbox	**textbox;
	char		*line;

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\ttextbox:"))
		gui_error(12);
	if (!(textbox = (t_textbox **)malloc(sizeof(t_textbox *) * qt)))
		error(1);
	gui_parse_cnt_txb_suite(textbox, fd, qt, id);
	return (textbox);
}

t_checkbox	**gui_parse_container_checkbox(int fd, int qt)
{
	t_checkbox	**checkbox;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\tcheckbox:"))
		gui_error(10);
	if (!(checkbox = (t_checkbox **)malloc(sizeof(t_checkbox *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		checkbox[i] = gui_parse_checkbox(fd, 6);
		checkbox[i]->selected = 0;
		i++;
		if (i < qt)
		{
			get_next_line(fd, &line);
			if (ft_strcmp(line, "\t\t,"))
				gui_error(11);
		}
	}
	return (checkbox);
}

void		gui_parse_container(t_gui *gui, int fd, int id)
{
	char	*line;

	gui_parse_container_info(gui, fd, id, 11);
	if (CONTAINER->button_qt > 0)
		BUTTON = gui_parse_container_button(fd, CONTAINER->button_qt, id);
	if (CONTAINER->scroll_qt > 0)
		SCROLL = gui_parse_container_scroll(fd, CONTAINER->scroll_qt, id);
	if (CONTAINER->textbox_qt > 0)
		TEXTBOX = gui_parse_container_textbox(fd, CONTAINER->textbox_qt, id);
	if (CONTAINER->checkbox_qt > 0)
		CHECKBOX = gui_parse_container_checkbox(fd, CONTAINER->checkbox_qt);
	get_next_line(fd, &line);
	if (ft_strcmp(line, "\t,"))
		gui_error(10);
}

void	gui_parse_main_builder(t_gui *gui, int fd, int nb)
{
	int		id;

	id = 0;
	if (!(gui->container = (t_container **)malloc(sizeof(t_container *)
	* GUI_CONTAINER_TOTAL_NB)))
		error(1);
	while (id < nb)
	{
		if (!(CONTAINER = (t_container *)malloc(sizeof(t_container))))
			error(1);
		if (!(CONTAINER->txt = (t_txt *)malloc(sizeof(t_txt))))
			error(1);
		CONTAINER->button = NULL;
		CONTAINER->scroll = NULL;
		CONTAINER->textbox = NULL;
		CONTAINER->checkbox = NULL;
		CONTAINER->gauge = NULL;
		CONTAINER->txt->content = NULL;
		CONTAINER->txt->anchor = NULL;
		CONTAINER->txt->align = -1;
		CONTAINER->nature = CNT;
		gui_parse_container(gui, fd, id);
		id++;
	}
}
