/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_container.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:57:23 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 16:39:44 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		gui_container_draw_lim(t_gui *gui)
{
	int i;
	
	i = 0;
	while (i < GUI_WIDTH)
	{
		gui->color = gui_color("white");
		gui_pixel_put(gui, i, gui->tmp_lim);
		i++;
	}
}
