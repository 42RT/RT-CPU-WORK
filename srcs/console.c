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

#ifdef __APPLE__
# include <SDL.h>
#else
# include <SDL2/SDL.h>
#endif
#include <raytracer.h>
#include <gui.h>

static void	console_aff(t_env *e, char *str)
{
	SDL_Rect			area;
	static TTF_Font		*font = 0;
	static SDL_Color	color[2] = {{42, 0, 242, 255}, {42, 242, 42, 255}};

	if (!font)
		font = font_init("Starjedi.ttf");
	TTF_SizeText(font, "save: ", NULL, &(area.h));
	console_draw_area(e, &area);
	console_write_prompt(e, &area, color, font);
	console_write_userdata(e, &area, str, font);
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
			save_image(e->gfx->buff[BUFF_NB], ft_newstrcat(str, ".bmp"));
		return (0);
	}
	return (keycode != SDLK_ESCAPE);
}
