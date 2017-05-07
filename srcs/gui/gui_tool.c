/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:49:26 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_txt_to_texture(char *content, char *style, char *color)
{
	t_gui		*gui;
	SDL_Surface	*tmp;

	gui = get_gui();
	TTF_SizeText(TTF->font, content, &TTF->w_px, &TTF->h_px);
	if (!ft_strcmp(style, "SOLID"))
		tmp = TTF_RenderText_Solid(TTF->font, content, gui_color(color));
	else if (!ft_strcmp(style, "BLENDED"))
		tmp = TTF_RenderText_Blended(TTF->font, content, gui_color(color));
	else
		tmp = TTF_RenderText_Solid(TTF->font, content, gui_color(color));
	TTF->texture = SDL_CreateTextureFromSurface(gui->img, tmp);
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	SDL_FreeSurface(tmp);
}

void		gui_free_carray(char ***array, int dimension)
{
	int	i;

	i = 0;
	if (array && *array)
	{
		while (i < dimension)
			free((*array)[i++]);
		free(*array);
		*array = NULL;
	}
}

void		gui_free_str(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

SDL_Rect	gui_get_container_rect(int id)
{
	t_gui	*gui;

	gui = get_gui();
	if (id == -1)
		return (PARAM->dest);
	else
		return (CONTAINER->dest);
}
