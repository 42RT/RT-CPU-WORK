/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_textbox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:36:31 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_textbox_3(t_textbox *textbox, char **tmp)
{
	char	**tmp2;

	if (!CMP(tmp[0], "\t\ttxt"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		textbox->txt->content = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\t\ttxt_anchor"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		textbox->txt->anchor = ft_strdup(tmp2[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttag"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		textbox->tag = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

void		gui_parse_textbox_2(t_textbox *textbox, char **tmp)
{
	if (!CMP(tmp[0], "\t\ttxt_align"))
		textbox->txt->align = ft_atoi(tmp[1]);
	else if (!CMP(tmp[0], "\t\tmin"))
	{
		textbox->min = ft_atoi(tmp[1]);
		if (textbox->min >= 0)
			textbox->reserved = 0;
		else
			textbox->reserved = 1;
	}
	else if (!CMP(tmp[0], "\t\tmax"))
		textbox->max = ft_atoi(tmp[1]);
	else
		gui_parse_textbox_3(textbox, tmp);
}

t_textbox	*gui_parse_textbox(int fd, int nb)
{
	t_textbox	*textbox;
	char		**tmp;
	char		*line;

	textbox = gui_textbox_init();
	while (0 < nb--)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\t\tx"))
			textbox->dest.x = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ty"))
			textbox->dest.y = ft_atoi(tmp[1]);
		else
			gui_parse_textbox_2(textbox, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
	return (textbox);
}
