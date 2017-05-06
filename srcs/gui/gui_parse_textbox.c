/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_textbox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_get_textbox_value_suite(t_textbox *textbox, t_env *e)
{
	if (!ft_strcmp(textbox->tag, "__A"))
		textbox->value = gui_get_textbox_a();
	else if (!ft_strcmp(textbox->tag, "SIZ"))
		textbox->value = gui_get_textbox_siz();
	else if (!ft_strcmp(textbox->tag, "RFR"))
		textbox->value = gui_get_textbox_rfr();
	else if (!ft_strcmp(textbox->tag, "RFL"))
		textbox->value = gui_get_textbox_rfl();
	else if (!ft_strcmp(textbox->tag, "CPX"))
		textbox->value = ft_itoa(e->set->cam->pos.x);
	else if (!ft_strcmp(textbox->tag, "CPY"))
		textbox->value = ft_itoa(e->set->cam->pos.y);
	else if (!ft_strcmp(textbox->tag, "CPZ"))
		textbox->value = ft_itoa(e->set->cam->pos.z);
	else if (!ft_strcmp(textbox->tag, "CAX"))
		textbox->value = ft_itoa(e->set->cam->ang.x);
	else if (!ft_strcmp(textbox->tag, "CAY"))
		textbox->value = ft_itoa(e->set->cam->ang.y);
	else if (!ft_strcmp(textbox->tag, "CAZ"))
		textbox->value = ft_itoa(e->set->cam->ang.z);
	else
		event_txb_value_clear(textbox, textbox->maxlen);
}

void		gui_get_textbox_value(t_textbox *textbox)
{
	t_env	*e;

	e = get_env();
	gui_textbox_get_len(textbox);
	if (!ft_strcmp(textbox->tag, "__X"))
		textbox->value = gui_get_textbox_x();
	else if (!ft_strcmp(textbox->tag, "__Y"))
		textbox->value = gui_get_textbox_y();
	else if (!ft_strcmp(textbox->tag, "__Z"))
		textbox->value = gui_get_textbox_z();
	else if (!ft_strcmp(textbox->tag, "_AX"))
		textbox->value = gui_get_textbox_ax();
	else if (!ft_strcmp(textbox->tag, "_AY"))
		textbox->value = gui_get_textbox_ay();
	else if (!ft_strcmp(textbox->tag, "_AZ"))
		textbox->value = gui_get_textbox_az();
	else if (!ft_strcmp(textbox->tag, "__R"))
		textbox->value = gui_get_textbox_r();
	else if (!ft_strcmp(textbox->tag, "__G"))
		textbox->value = gui_get_textbox_g();
	else if (!ft_strcmp(textbox->tag, "__B"))
		textbox->value = gui_get_textbox_b();
	else
		gui_get_textbox_value_suite(textbox, e);
}

void		gui_parse_textbox_suite(t_textbox *textbox, char **tmp)
{
	if (!ft_strcmp(tmp[0], "\t\tmin"))
	{
		textbox->min = ft_atoi(tmp[1]);
		if (textbox->min >= 0)
			textbox->reserved = 0;
		else
			textbox->reserved = 1;
	}
	else if (!ft_strcmp(tmp[0], "\t\tmax"))
		textbox->max = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\t\ttxt"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		textbox->txt->content = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
	{
		tmp = ft_strsplit(tmp[1], '"');
		textbox->txt->anchor = ft_strdup(tmp[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
		textbox->txt->align = ft_atoi(tmp[1]);
}

t_textbox	*gui_parse_textbox(int fd, int nb)
{
	t_textbox	*textbox;
	char		**tmp;
	char		*line;
	int			i;

	textbox = gui_textbox_init();
	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\t\tx"))
			textbox->dest.x = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ty"))
			textbox->dest.y = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ttag"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			textbox->tag = ft_strdup(tmp[1]);
		}
		else
			gui_parse_textbox_suite(textbox, tmp);
		gui_free_array((void **)tmp, 2);
	}
	return (textbox);
}
