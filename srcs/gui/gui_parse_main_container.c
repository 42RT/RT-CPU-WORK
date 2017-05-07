/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_main_container.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 10:45:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

t_textbox	**gui_parse_container_textbox(int fd, int qt, int id)
{
	t_textbox	**textbox;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (CMP(line, "\ttextbox:"))
		gui_error(12);
	gui_free_str(&line);
	if (!(textbox = (t_textbox **)malloc(sizeof(t_textbox *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		textbox[i] = gui_parse_textbox(fd, 8);
		textbox[i]->p = id;
		textbox[i]->id = i;
		gui_get_textbox_value(textbox[i]);
		gui_textbox_set(textbox[i++], gui_get_container_rect(id));
		if (i < qt)
			gui_parse_widget_coma(fd);
	}
	return (textbox);
}

t_checkbox	**gui_parse_container_cbx(int fd, int qt, int id)
{
	t_checkbox	**checkbox;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (CMP(line, "\tcheckbox:"))
		gui_error(12);
	gui_free_str(&line);
	if (!(checkbox = (t_checkbox **)malloc(sizeof(t_checkbox *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		checkbox[i] = gui_parse_checkbox(fd, 7);
		checkbox[i]->p = id;
		checkbox[i]->id = i;
		checkbox[i]->selected = 0;
		gui_checkbox_set(checkbox[i++], gui_get_container_rect(id));
		if (i < qt)
			gui_parse_widget_coma(fd);
	}
	return (checkbox);
}

void		gui_parse_container(t_gui *gui, int fd, int id)
{
	gui_parse_container_info(gui, fd, id, 11);
	if (CONTAINER->button_qt > 0)
		BUTTON = gui_parse_container_button(fd, CONTAINER->button_qt, id);
	if (CONTAINER->scroll_qt > 0)
		SCROLL = gui_parse_container_scroll(fd, CONTAINER->scroll_qt, id);
	if (CONTAINER->textbox_qt > 0)
		TEXTBOX = gui_parse_container_textbox(fd, CONTAINER->textbox_qt, id);
	if (CONTAINER->checkbox_qt > 0)
		CHECKBOX = gui_parse_container_cbx(fd, CONTAINER->checkbox_qt, id);
	gui_parse_container_coma(fd);
}

void		gui_parse_main_builder(t_gui *gui, int fd, int nb)
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
