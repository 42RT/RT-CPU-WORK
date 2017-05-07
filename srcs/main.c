/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 20:34:57 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/09 16:52:51 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <raytracer.h>
#include <gui.h>

static void	ft_load_icon(t_env *e)
{
	SDL_Surface	*img;

	img = SDL_LoadBMP("ressources/icon.bmp");
	if (img)
	{
		SDL_SetWindowIcon(e->gfx->win, img);
		SDL_FreeSurface(img);
	}
}

void		ft_welcome(t_env *e)
{
	SDL_Surface	*img;
	SDL_Texture	*texture;
	SDL_Rect	pos;

	pos.x = 0;
	pos.y = 0;
	pos.w = e->set->width;
	pos.h = e->set->height;
	ft_load_icon(e);
	img = SDL_LoadBMP("ressources/background.bmp");
	if (img)
	{
		texture = SDL_CreateTextureFromSurface(e->gfx->renderer, img);
		if (texture)
		{
			SDL_FreeSurface(img);
			SDL_RenderCopy(e->gfx->renderer, texture, NULL, &pos);
			SDL_DestroyTexture(texture);
			SDL_RenderPresent(e->gfx->renderer);
			e->background = 1;
		}
	}
}

int			main(int ac, char **av)
{
	t_env		*e;

	setbuf(stdout, NULL);
	e = get_env();
	generate_noise(e);
	e->inside_obj = 0;
	e->last_refract = 1;
	if (ac == 2)
		e->scene = ft_strdup(av[1]);
	else if (ac == 1)
		e->scene = ft_strdup("scene/.default.rts");
	else
		error(2);
	init(e, e->scene);
	e->gfx = gfx_init(e->set->name, e->set->width,
							e->set->height, BUFF_NB + 1);
	if (!e->gfx)
		return (0);
	ft_welcome(e);
	SDL_RaiseWindow(e->gfx->win);
	while (1)
		wait_event(e);
	return (0);
}
