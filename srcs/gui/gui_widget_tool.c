/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_widget_tool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 05:23:43 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_widget_draw_depth(SDL_Rect widget, int px, char *color)
{
	int		i;
	int		j;
	t_gui	*gui;

	gui = get_gui();
	i = widget.x - px;
	while (i < widget.w + widget.x)
	{
		j = widget.y - px;
		while (j < widget.h + widget.y)
		{
			if (i < widget.x || j < widget.y)
			{
				gui->color = gui_color(color);
				gui_pixel_put(gui, i, j);
			}
			j++;
		}
		i++;
	}
}

void	gui_widget_draw_in_line(SDL_Rect widget, int px, char *color)
{
	int		i;
	int		j;
	t_gui	*gui;

	gui = get_gui();
	i = widget.x;
	while (i < widget.w + widget.x)
	{
		j = widget.y;
		while (j < widget.h + widget.y)
		{
			if (i < widget.x + px || i >= widget.x + widget.w - px
			|| j < widget.y + px || j >= widget.y + widget.h - px)
			{
				gui->color = gui_color(color);
				gui_pixel_put(gui, i, j);
			}
			j++;
		}
		i++;
	}
}

void	gui_widget_draw_outline(SDL_Rect widget, int px, char *color)
{
	int		i;
	int		j;
	t_gui	*gui;

	gui = get_gui();
	i = widget.x - px;
	while (i < widget.w + widget.x + px)
	{
		j = widget.y - px;
		while (j < widget.h + widget.y + px)
		{
			if (i < widget.x || i >= widget.x + widget.w
			|| j < widget.y || j >= widget.y + widget.h)
			{
				gui->color = gui_color(color);
				gui_pixel_put(gui, i, j);
			}
			j++;
		}
		i++;
	}
}

void	gui_widget_texture_get_bmp(void *widget, char *file)
{
	t_gui	*gui;
	char	*path;

	gui = get_gui();
	path = ft_strjoin(PATH->texture, file);
	((REF *)widget)->surface = SDL_LoadBMP(path);
	free(path);
	if (!((REF *)widget)->surface)
		gui_error(2);
	((REF *)widget)->bmp = SDL_CreateTextureFromSurface(gui->img,
		((REF *)widget)->surface);
	SDL_FreeSurface(((REF *)widget)->surface);
	if (!((REF *)widget)->bmp)
		gui_error(3);
}

void	gui_widget_display(void *widget)
{
	t_gui	*gui;

	gui = get_gui();
	SDL_RenderCopy(gui->img, ((REF *)widget)->bmp,
		NULL, &((REF *)widget)->dest);
	SDL_DestroyTexture(((REF *)widget)->bmp);
}
