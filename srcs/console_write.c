/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 01:29:15 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/06 01:29:16 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
# include <SDL.h>
#else
# include <SDL2/SDL.h>
#endif
#include <raytracer.h>
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
		|| (keycode >= '0' && keycode <= '9')
		|| keycode == SP_KEY) && len < 49)
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

void		console_draw_area(t_env *e, SDL_Rect *area)
{
	area->w = e->set->width;
	area->x = 0;
	area->y = e->set->height - area->h;
	gfx_blitz_image(e->gfx, 0, 0, e->gfx->buff[BUFF_NB]);
	SDL_SetRenderDrawBlendMode(e->gfx->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(e->gfx->renderer, 0, 0, 0, 192);
	SDL_RenderDrawRect(e->gfx->renderer, area);
	SDL_RenderFillRect(e->gfx->renderer, area);
}

void		console_write_prompt(t_env *e, SDL_Rect *area, SDL_Color *color,
									TTF_Font *font)
{
	SDL_Surface			*text;
	SDL_Texture			*texture;

	area->x = 7;
	--area->y;
	TTF_SizeText(font, "save: ", &(area->w), &(area->h));
	text = TTF_RenderText_Blended(font, "save: ", color[1]);
	texture = SDL_CreateTextureFromSurface(e->gfx->renderer, text);
	SDL_FreeSurface(text);
	SDL_RenderCopy(e->gfx->renderer, texture, NULL, area);
	SDL_DestroyTexture(texture);
}

void		console_write_userdata(t_env *e, SDL_Rect *area, char *str,
									TTF_Font *font)
{
	SDL_Surface			*text;
	SDL_Texture			*texture;

	area->x += area->w;
	TTF_SizeText(font, str, &(area->w), NULL);
	text = TTF_RenderText_Blended(font, str, (SDL_Color){42, 0, 242, 255});
	texture = SDL_CreateTextureFromSurface(e->gfx->renderer, text);
	SDL_FreeSurface(text);
	SDL_RenderCopy(e->gfx->renderer, texture, NULL, area);
	SDL_DestroyTexture(texture);
}
