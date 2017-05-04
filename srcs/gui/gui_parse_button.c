/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_button.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_button_suite(t_button *button, char **tmp)
{
	if (!ft_strcmp(tmp[0], "\t\tx"))
		button->dest.x = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\t\ty"))
		button->dest.y = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\t\taction"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		button->action = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		button->txt->content = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		button->txt->anchor = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
		button->txt->align = ft_atoi(tmp[1]);
}

t_button	*gui_parse_button(int fd, int nb)
{
	t_button	*button;
	char		**tmp;
	char		*line;
	int			i;

	button = gui_button_init();
	i = 0;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		gui_parse_button_suite(button, tmp);
		gui_free_array((void **)tmp, 2);
		i++;
	}
	return (button);
}
