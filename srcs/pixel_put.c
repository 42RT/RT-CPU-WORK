/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:59:45 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/11 17:45:16 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	pixel_put(t_env *env, t_color color)
{
	SDL_SetRenderDrawColor(env->img, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(env->img, env->y, env->x);
}

void	pixel_put_gui(t_gui	*gui, int x, int y)
{
	SDL_SetRenderDrawColor(gui->img, gui->color->r, gui->color->g, gui->color->b, 
			gui->color->a);
	SDL_RenderDrawPoint(gui->img, x, y);
}
