/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:59:45 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 17:37:40 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	pixel_put(t_env *env, t_color color)
{
	SDL_SetRenderDrawColor(env->img, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(env->img, env->y, env->x);
}
