/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/16 03:54:10 by jrouilly          #+#    #+#             */
/*   Updated: 2014/09/16 03:54:11 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	loading_bar(t_env *e, float percent, unsigned int color,
					unsigned int bgcolor)
{
	static SDL_Rect	area;
	static int		old;

	if ((int)(percent * 2) == old)
		return;
	old = (int)(percent * 2);
	area.x = e->set->width / 2 - 102;
	area.y = e->set->height / 2 - 7;
	area.w = 204;
	area.h = 14;

	SDL_SetRenderDrawColor(e->gfx->renderer, (bgcolor >> 16) & 0xFF,
							(bgcolor >> 8) & 0xFF, bgcolor & 0xFF, 255);
	SDL_RenderFillRect(e->gfx->renderer, &area);
	SDL_SetRenderDrawColor(e->gfx->renderer, (color >> 16) & 0xFF,
							(color >> 8) & 0xFF, color & 0xFF, 255);
	SDL_RenderDrawRect(e->gfx->renderer, &area);
	area.x += 2;
	area.y += 2;
	area.h -= 4;
	area.w = (int)(percent * 2);
	SDL_RenderDrawRect(e->gfx->renderer, &area);
	SDL_RenderFillRect(e->gfx->renderer, &area);
	//ajouter pourcentage
	SDL_RenderPresent(e->gfx->renderer);
}