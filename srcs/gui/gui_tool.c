/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

char	*str_tolower(char *str)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 10)))
		error(1);
	while (i < ft_strlen(str))
	{
		if (str[i] >= 65 && str[i] <= 90)
			tmp[i] = str[i] + 32;
		else
			tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	gui_txt_to_texture(char *content, char *style, char *color)
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

void	gui_free_array(void **array, int dimension)
{
	int	i;

	i = 0;
	while (i < dimension)
		free(array[i++]);
	free(array);
	array = NULL;
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
