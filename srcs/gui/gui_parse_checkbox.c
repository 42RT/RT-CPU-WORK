/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_checkbox.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 10:49:15 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_checkbox_state(t_checkbox *checkbox, char **tmp)
{
	if (!CMP(tmp[1], " false"))
		checkbox->selected = 0;
	else if (!CMP(tmp[1], " true"))
		checkbox->selected = 1;
	else
		gui_error(17);
}

void		gui_parse_checkbox_suite(t_checkbox *checkbox, char **tmp)
{
	char	**tmp2;

	if (!CMP(tmp[0], "\t\ttag"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		checkbox->tag = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\t\ttxt"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		checkbox->txt->content = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\t\ttxt_anchor"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		checkbox->txt->anchor = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

t_checkbox	*gui_parse_checkbox(int fd, int nb)
{
	t_checkbox	*checkbox;
	char		**tmp;
	char		*line;
	int			i;

	checkbox = gui_checkbox_init();
	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!CMP(tmp[0], "\t\tx"))
			checkbox->dest.x = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\ty"))
			checkbox->dest.y = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\ttxt_align"))
			checkbox->txt->align = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\tselected"))
			gui_parse_checkbox_state(checkbox, tmp);
		else
			gui_parse_checkbox_suite(checkbox, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
	return (checkbox);
}
