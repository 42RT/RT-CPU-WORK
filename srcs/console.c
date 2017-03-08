/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 02:56:50 by jrouilly          #+#    #+#             */
/*   Updated: 2015/10/18 13:03:41 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#ifdef __APPLE__
# include <SDL.h>
#else
# include <SDL2/SDL.h>
#endif
#include <gui.h>

void		write_console(int keycode, char *str)
{
	char	c[2];
	int		len;

	c[0] = 0;
	c[1] = 0;
	len = ft_strlen(str);
	if (len >= 49)
		return ;
	if (((keycode >= 'a' && keycode <= 'z')
		|| (keycode >= '0' && keycode <= '9') || keycode == SP_KEY) && len < 49)
	{
		c[0] = keycode;
		ft_strcat(str, c);
	}
	if (keycode == ECHAP_KEY)
		str[0] = 0;
}

TTF_Font	*font_init(char *name)
{
	TTF_Font	*font;
	char		*path;

	path = ft_newstrcat(TTF_PATH, name);
	font = TTF_OpenFont(path, 14);
	free(path);
	return (font);
}

static void	console_aff(t_env *e, char *str)
{
	SDL_Rect			area;
	static TTF_Font		*font = 0;
	static SDL_Color	color[2] = {{42, 0, 242, 255}, {42, 242, 42, 255}};
	SDL_Surface 		*text;
	SDL_Texture			*texture;

	if (!font)
		font = font_init("Starjedi.ttf");
	TTF_SizeText(font, "save: ", NULL, &(area.h));

	area.w = e->set->width;
	area.x = 0;
	area.y = e->set->height - area.h;
	libxmlx_blitz_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
	SDL_SetRenderDrawBlendMode(e->gfx->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(e->gfx->renderer, 0, 0, 0, 192);
	SDL_RenderDrawRect(e->gfx->renderer, &area);
	SDL_RenderFillRect(e->gfx->renderer, &area);

	area.x = 7;
	--area.y;
	TTF_SizeText(font, "save: ", &(area.w), &(area.h));
	text = TTF_RenderText_Blended(font, "save: ", color[1]);
	texture = SDL_CreateTextureFromSurface(e->gfx->renderer, text);
	SDL_FreeSurface(text);
	SDL_RenderCopy(e->gfx->renderer, texture, NULL, &area);
	SDL_DestroyTexture(texture);

	area.x += area.w;
	TTF_SizeText(font, str, &(area.w), NULL);
	text = TTF_RenderText_Blended(font, str, color[0]);
	texture = SDL_CreateTextureFromSurface(e->gfx->renderer, text);
	SDL_FreeSurface(text);
	SDL_RenderCopy(e->gfx->renderer, texture, NULL, &area);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(e->gfx->renderer);
	free(str);
}

int			rt_console(int keycode, t_env *e, int free_buff)
{
	static char	str[50] = "";

	if (free_buff)
		ft_bzero(str, 50);
	if ((keycode >= 'a' && keycode <= 'z') || keycode == SDLK_ESCAPE
			|| keycode == SDLK_SPACE)
		write_console(keycode, str);
	if (keycode == SDLK_BACKSPACE)
		str[ft_strlen(str) - 1] = 0;
	console_aff(e, *str ? ft_newstrcat(str, ".bmp") : ft_strdup(str));
	if (keycode == SDLK_RETURN)
	{
		if (str[0])
			save_image(e->gfx->buff[e->gfx->act], str);
		return (0);
	}
	return (keycode != SDLK_ESCAPE);
}
