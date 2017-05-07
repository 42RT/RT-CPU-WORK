/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_main_container_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:05:03 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_container_info_3(t_gui *gui, char **tmp, int id)
{
	char	**tmp2;

	if (!CMP(tmp[0], "\ttxt"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		if (tmp2[1])
			CONTAINER->txt->content = ft_strdup(tmp2[1]);
		else
			CONTAINER->txt->content = NULL;
	}
	else if (!CMP(tmp[0], "\ttxt_anchor"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		if (tmp2[1])
			CONTAINER->txt->anchor = ft_strdup(tmp2[1]);
		else
			CONTAINER->txt->anchor = NULL;
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

void		gui_parse_container_info_2(t_gui *gui, char **tmp, int id)
{
	if (!CMP(tmp[0], "\tw"))
		CONTAINER->dest.w = ft_atoi(tmp[1]);
	else if (!CMP(tmp[0], "\th"))
		CONTAINER->dest.h = ft_atoi(tmp[1]);
	else if (!CMP(tmp[0], "\ttxt_align"))
		CONTAINER->txt->align = ft_atoi(tmp[1]);
	else if (!CMP(tmp[0], "\tbutton_qt"))
		CONTAINER->button_qt = ft_atoi(tmp[1]);
	else if (!CMP(tmp[0], "\tscroll_qt"))
		CONTAINER->scroll_qt = ft_atoi(tmp[1]);
	else if (!CMP(tmp[0], "\ttextbox_qt"))
		CONTAINER->textbox_qt = ft_atoi(tmp[1]);
	else if (!CMP(tmp[0], "\tcheckbox_qt"))
		CONTAINER->checkbox_qt = ft_atoi(tmp[1]);
	else
		gui_parse_container_info_3(gui, tmp, id);
}

void		gui_parse_container_info(t_gui *gui, int fd, int id, int nb)
{
	int		i;
	char	**tmp;
	char	*line;

	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!CMP(tmp[0], "\tx"))
			CONTAINER->dest.x = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\ty"))
			CONTAINER->dest.y = ft_atoi(tmp[1]);
		else
			gui_parse_container_info_2(gui, tmp, id);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
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
	if (CMP(line, "\tbutton:"))
		gui_error(12);
	gui_free_str(&line);
	if ((button = (t_button **)malloc(sizeof(t_button *) * qt)) == NULL)
		error(1);
	i = 0;
	while (i < qt)
	{
		button[i] = gui_parse_button(fd, 6);
		button[i]->p = id;
		button[i]->id = i;
		gui_button_set(button[i++], gui_get_container_rect(id));
		if (i < qt)
			gui_parse_widget_coma(fd);
	}
	return (button);
}

t_scroll	**gui_parse_container_scroll(int fd, int qt, int id)
{
	t_scroll	**scroll;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (CMP(line, "\tscroll:"))
		gui_error(12);
	gui_free_str(&line);
	if (!(scroll = (t_scroll **)malloc(sizeof(t_scroll *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		scroll[i] = gui_parse_scroll(fd, 6);
		scroll[i]->p = id;
		scroll[i]->id = i;
		scroll[i]->value = gui_get_scroll_value(scroll[i]);
		gui_scroll_set(scroll[i++], gui_get_container_rect(id));
		if (i < qt)
			gui_parse_widget_coma(fd);
	}
	return (scroll);
}
