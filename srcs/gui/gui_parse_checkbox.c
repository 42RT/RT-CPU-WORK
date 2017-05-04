/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_checkbox.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_checkbox_suite(t_checkbox *checkbox, char **tmp)
{
	if (!ft_strcmp(tmp[0], "\t\tx"))
		checkbox->dest.x = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\t\ty"))
		checkbox->dest.y = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\t\ttag"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		checkbox->tag = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		checkbox->txt->content = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		checkbox->txt->anchor = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
		checkbox->txt->align = ft_atoi(tmp[1]);
}

t_checkbox	*gui_parse_checkbox(int fd, int nb)
{
	t_checkbox	*checkbox;
	char		**tmp;
	char		*line;
	int			i;

	i = 0;
	if (!(checkbox = (t_checkbox *)malloc(sizeof(t_checkbox))))
		error(1);
	if (!(checkbox->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	checkbox->nature = CBX;
	checkbox->surface = NULL;
	checkbox->bmp = NULL;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		gui_parse_checkbox_suite(checkbox, tmp);
		gui_free_array((void **)tmp, 2);
		i++;
	}
	return (checkbox);
}
