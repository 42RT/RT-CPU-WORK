/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_widget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:00:14 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/11 18:19:31 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	gui_widget_add()
{
	;
}

void	gui_widget_new_suite(int x, int y, int width,int height)
{
	;
}

void	gui_widget_new(t_gui *gui, char *name, char *type, char *action)
{
	t_widget *tmp;

	tmp = 
	while (gui->widget->next)
}

void	gui_widget_init(t_gui *gui)
{
	if (gui->widget = (t_widget*)malloc(sizeof(widget)) = NULL)
		error(1);
	gui->widget->name = "GUI_MAIN";
	gui->widget->type = "CONTAINER";
	gui->widget->action = NULL;
	gui->widget->x = 0;
	gui->widget->y = 0;
	gui->widget->width = gui->width;
	gui->widget->height = gui->height;
	gui->widget->next = NULL;
}
