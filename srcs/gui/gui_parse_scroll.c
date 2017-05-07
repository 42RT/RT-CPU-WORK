/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_scroll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:12:16 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_scroll_suite(t_scroll *scroll, char **tmp)
{
	char	**tmp2;

	tmp2 = NULL;
	if (!ft_strcmp(tmp[0], "\t\ttag"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		scroll->tag = ft_strdup(tmp2[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		scroll->txt->content = ft_strdup(tmp2[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		scroll->txt->anchor = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_carray(&tmp2, 2);
}

t_scroll	*gui_parse_scroll(int fd, int nb)
{
	t_scroll	*scroll;
	char		**tmp;
	char		*line;

	scroll = gui_scroll_init();
	while (0 < nb--)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\t\tx"))
			scroll->dest.x = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ty"))
			scroll->dest.y = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
			scroll->txt->align = ft_atoi(tmp[1]);
		else
			gui_parse_scroll_suite(scroll, tmp);
		gui_free_carray(&tmp, 2);
		gui_free_str(&line);
	}
	return (scroll);
}

char		**gui_get_scroll_value_def(t_scroll *scroll)
{
	char	**value;

	scroll->nb_value = 1;
	scroll->active_value = 0;
	scroll->mod = 0;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = "unset scroll";
	return (value);
}

char		**gui_get_scroll_value(t_scroll *scroll)
{
	t_gui	*gui;
	t_env	*e;

	e = get_env();
	gui = get_gui();
	if (!ft_strcmp(scroll->tag, "SCN"))
		return (gui_get_scroll_scene(scroll, gui));
	else if (!ft_strcmp(scroll->tag, "OBJ"))
		return (gui_get_scroll_object(scroll, e));
	else if (!ft_strcmp(scroll->tag, "_AA"))
		return (gui_get_scroll_aa(scroll));
	else if (!ft_strcmp(scroll->tag, "RES"))
		return (gui_get_scroll_res(scroll));
	else if (!ft_strcmp(scroll->tag, "NML"))
		return (gui_get_scroll_texture_nml(scroll));
	else if (!ft_strcmp(scroll->tag, "PCD"))
		return (gui_get_scroll_texture_pcd(scroll));
	else if (!ft_strcmp(scroll->tag, "MTR"))
		return (gui_get_scroll_texture_mtr(scroll));
	else
		return (gui_get_scroll_value_def(scroll));
}
