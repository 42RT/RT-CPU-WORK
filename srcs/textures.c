/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:23:05 by rfriscca          #+#    #+#             */
/*   Updated: 2017/03/17 14:23:07 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <stdio.h>

unsigned int	get_pixel(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;
	unsigned int	color;

	x = x % surface->w;
	y = y % surface->h / 2;
	pixels = (unsigned int *)surface->pixels;
	color = 0;
	color += pixels[(y * surface->w) + x] & surface->format->Rmask;
	color += pixels[(y * surface->w) + x] & surface->format->Gmask;
	color += pixels[(y * surface->w) + x] & surface->format->Bmask;
	return (color);
}
