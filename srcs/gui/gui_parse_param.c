/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 01:27:31 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_init_param(t_gui *gui)
{
	if (!(PARAM = (t_param *)malloc(sizeof(t_param))))
		error(1);
	PARAM->nature = PRM;
	PARAM->button = NULL;
	PARAM->scroll = NULL;
	PARAM->textbox = NULL;
	PARAM->checkbox = NULL;
	PARAM->gauge = NULL;
	PARAM->active = 0;
}

void	gui_parse_param_setting(t_gui *gui, char **tmp)
{
	if (!ft_strcmp(tmp[0], "\tx"))
		PARAM->dest.x = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\ty"))
		PARAM->dest.y = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tw"))
		PARAM->dest.w = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\th"))
		PARAM->dest.h = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tbutton_qt"))
		PARAM->button_qt = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tscroll_qt"))
		PARAM->scroll_qt = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\ttextbox_qt"))
		PARAM->textbox_qt = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tcheckbox_qt"))
		PARAM->checkbox_qt = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tgauge_qt"))
		PARAM->gauge_qt = ft_atoi(tmp[1]);
	else if (!ft_strcmp(tmp[0], "\tfreetxt_qt"))
		PARAM->freetxt_qt = ft_atoi(tmp[1]);
}

void	gui_parse_param_builder(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	gui_init_param(gui);
	i = 0;
	while (nb > i++)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		gui_parse_param_setting(gui, tmp);
		gui_free_array((void ***)&tmp, 2);
	}
	if (PARAM->button_qt > 0)
		PARAM->button = gui_parse_container_button(fd, PARAM->button_qt, -1);
	if (PARAM->scroll_qt > 0)
		PARAM->scroll = gui_parse_container_scroll(fd, PARAM->scroll_qt, -1);
	if (PARAM->textbox_qt > 0)
		PARAM->textbox = gui_parse_container_textbox(fd, PARAM->textbox_qt, -1);
	if (PARAM->checkbox_qt > 0)
		PARAM->checkbox = gui_parse_container_cbx(fd, PARAM->checkbox_qt, -1);
	if (PARAM->gauge_qt > 0)
		PARAM->gauge = gui_parse_container_gauge(fd, PARAM->gauge_qt, -1);
	if (PARAM->freetxt_qt > 0)
		PARAM->freetxt = gui_parse_container_freetxt(fd, PARAM->freetxt_qt, -1);
}
