/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_pixel_put(t_gui *gui, int x, int y)
{
	SDL_SetRenderDrawColor(gui->img, gui->color.r, gui->color.g,
		gui->color.b, gui->color.a);
	SDL_RenderDrawPoint(gui->img, x, y);
}

SDL_Color	gui_color_data_set(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

SDL_Color	gui_color(char *choice)
{
	if (!ft_strcmp(choice, "white"))
		return (gui_color_data_set(255, 255, 255, 255));
	if (!ft_strcmp(choice, "black"))
		return (gui_color_data_set(0, 0, 0, 255));
	if (!ft_strcmp(choice, "red brick"))
		return (gui_color_data_set(130, 5, 5, 255));
	if (!ft_strcmp(choice, "red"))
		return (gui_color_data_set(255, 0, 0, 255));
	if (!ft_strcmp(choice, "purple deep"))
		return (gui_color_data_set(31, 17, 70, 255));
	if (!ft_strcmp(choice, "teal"))
		return (gui_color_data_set(43, 202, 189, 255));
	else
		return (gui_color_data_set(0, 0, 0, 0));
}
