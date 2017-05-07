/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_button.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 10:47:51 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_button_suite(t_button *button, char **tmp)
{
	char	**tmp2;

	if (!CMP(tmp[0], "\t\taction"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		button->action = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\t\ttxt"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		button->txt->content = ft_strdup(tmp2[1]);
	}
	else if (!CMP(tmp[0], "\t\ttxt_anchor"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		button->txt->anchor = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

t_button	*gui_parse_button(int fd, int nb)
{
	t_button	*button;
	char		**tmp;
	char		*line;
	int			i;

	button = gui_button_init();
	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!CMP(tmp[0], "\t\tx"))
			button->dest.x = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\ty"))
			button->dest.y = ft_atoi(tmp[1]);
		else if (!CMP(tmp[0], "\t\ttxt_align"))
			button->txt->align = ft_atoi(tmp[1]);
		else
			gui_parse_button_suite(button, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
	return (button);
}
