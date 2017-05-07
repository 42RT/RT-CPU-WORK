/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_main_container_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:05:34 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

t_freetxt	**gui_parse_container_freetxt(int fd, int qt, int id)
{
	t_freetxt	**freetxt;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (CMP(line, "\tfreetxt:"))
		gui_error(12);
	gui_free_str(&line);
	if (!(freetxt = (t_freetxt **)malloc(sizeof(t_freetxt *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		freetxt[i] = gui_parse_freetxt(fd, 4);
		freetxt[i]->p = id;
		freetxt[i]->id = i;
		gui_freetxt_set(freetxt[i++], gui_get_container_rect(id));
		if (i < qt)
			gui_parse_widget_coma(fd);
	}
	return (freetxt);
}

t_gauge		**gui_parse_container_gauge(int fd, int qt, int id)
{
	t_gauge	**gauge;
	char	*line;
	int		i;

	get_next_line(fd, &line);
	if (CMP(line, "\tgauge:"))
		gui_error(12);
	gui_free_str(&line);
	if (!(gauge = (t_gauge **)malloc(sizeof(t_gauge *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		gauge[i] = gui_parse_gauge(fd, 8);
		gauge[i]->p = id;
		gauge[i]->id = i;
		gui_gauge_set(gauge[i]);
		gui_gauge_get_value(gauge[i++]);
		if (i < qt)
			gui_parse_widget_coma(fd);
	}
	return (gauge);
}
