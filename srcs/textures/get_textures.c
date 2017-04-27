/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:35:05 by rfriscca          #+#    #+#             */
/*   Updated: 2017/04/24 13:35:06 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

t_vector		get_normalmap(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;
	t_vector		n;

	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	x = x % surface->w;
	y = y % surface->h;
	pixels = (unsigned int *)surface->pixels;
	n.x = (pixels[(y * surface->w) + x] & surface->format->Rmask) >> 16;
	n.y = (pixels[(y * surface->w) + x] & surface->format->Gmask) >> 8;
	n.z = pixels[(y * surface->w) + x] & surface->format->Bmask;
	n.x = n.x / 255 * 2 - 1;
	n.y = n.y / 255 * 2 - 1;
	n.z = n.z / 255 * 2 - 1;
	normalize(&n);
	return (n);
}

t_color			get_pixel(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;
	t_color			color;

	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	x = x % surface->w;
	y = y % surface->h;
	pixels = (unsigned int *)surface->pixels;
	color.r = (pixels[(y * surface->w) + x] & surface->format->Rmask) >> 16;
	color.g = (pixels[(y * surface->w) + x] & surface->format->Gmask) >> 8;
	color.b = pixels[(y * surface->w) + x] & surface->format->Bmask;
	return (color);
}

void			get_x_y_value(t_ray_data *d, int *x, int *y)
{
	if (d->shorter->type & (CYLINDER | CONE | PLANE | SQUARE | DISK))
	{
		*x = ((int)d->o->x + (int)d->o->z * sin(d->shorter->ang.x)) / 10;
		*y = ((int)d->o->y * sin(d->shorter->ang.x) + (int)d->o->z *
		cos(d->shorter->ang.x)) / 10;
	}
	else
	{
		*x = (int)d->o->x / 5;
		*y = ((int)d->o->y + (int)d->o->z) / 10;
	}
}

void			choose_texture(t_ray_data *d, float turb)
{
	int		x;
	int		y;

	get_x_y_value(d, &x, &y);
	if (d->shorter->normalmap && d->shorter->nm_surface)
	{
		SDL_LockSurface(d->shorter->nm_surface);
		d->n = get_normalmap(d->shorter->nm_surface, x, y);
		SDL_UnlockSurface(d->shorter->nm_surface);
	}
	if (!ft_strncmp(d->shorter->procedural, "marble", 6))
		d->shorter->color = stripe(d->shorter, turb, x);
	else if (!ft_strncmp(d->shorter->procedural, "stripe", 6))
		d->shorter->color = stripe(d->shorter, 0, x);
	else if (!ft_strncmp(d->shorter->procedural, "square", 6))
		d->shorter->color = square(d->shorter, 0, x, y);
	else if (!ft_strncmp(d->shorter->procedural, "perlin", 6))
		d->shorter->color = perlin(d->shorter->color, turb);
	else if (d->shorter->texture && d->shorter->tex_surface)
	{
		SDL_LockSurface(d->shorter->tex_surface);
		d->shorter->color = get_pixel(d->shorter->tex_surface, x, y);
		SDL_UnlockSurface(d->shorter->tex_surface);
	}
}
