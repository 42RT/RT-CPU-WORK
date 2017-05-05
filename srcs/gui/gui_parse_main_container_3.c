/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_main_container_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
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
		{
			get_next_line(fd, &line);
			if (CMP(line, "\t\t,"))
				gui_error(11);
		}
	}
	return (freetxt);
}
