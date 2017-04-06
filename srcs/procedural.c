/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:27:19 by rfriscca          #+#    #+#             */
/*   Updated: 2017/02/09 15:09:32 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

t_vector		get_normalmap(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;
	t_vector		n;

	x = x % surface->w;
	y = y % surface->h;
	pixels = (unsigned int *)surface->pixels;
	n.x = (pixels[(y * surface->w) + x] & surface->format->Rmask) >> 16;
	n.y = (pixels[(y * surface->w) + x] & surface->format->Gmask) >> 8;
	n.z = pixels[(y * surface->w) + x] & surface->format->Bmask;
	n.x = n.x / 255 * 2 - 1;
	n.y = n.y / 255 * 2 - 1;
	n.z = n.z / 255 * 2 - 1;
	return (n);
}

t_color			get_pixel(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;
	t_color			color;

	x = x % surface->w;
	y = y % surface->h;
	pixels = (unsigned int *)surface->pixels;
	color.r = (pixels[(y * surface->w) + x] & surface->format->Rmask) >> 16;
	color.g = (pixels[(y * surface->w) + x] & surface->format->Gmask) >> 8;
	color.b = pixels[(y * surface->w) + x] & surface->format->Bmask;
	return (color);
}

t_color			skybox(float turb)
{
	t_color		 	color;
	float			ocolor[3];

	turb /= 255;
	ocolor[0] = 70 + 185 * turb;
	ocolor[1] = 190 + 65 * turb;
	ocolor[2] = 255;
	color.r = (unsigned int)ocolor[0];
	color.g = (unsigned int)ocolor[1];
	color.b = (unsigned int)ocolor[2];
	return (color);
}

t_color			perlin(t_color objcolor, float turb)
{
	t_color			color;

	turb /= 255;
	color.r = objcolor.r * turb;
	color.g = objcolor.g * turb;
	color.b = objcolor.b * turb;
	return (color);
}

t_color			square(t_env *e, t_obj *obj, float turb)
{
	t_color 		color;
	float			ocolor[3];

	turb *= 0.3;
	ocolor[0] = (float)(obj->color.r) / 255;
	ocolor[1] = (float)(obj->color.g) / 255;
	ocolor[2] = (float)(obj->color.b) / 255;
	ocolor[0] *= ((1 + sin(e->x + turb)) / 4 + (1 + cos(e->y + turb)) / 4) * 255;
	ocolor[1] *= ((1 + sin(e->x + turb)) / 4 + (1 + cos(e->y + turb)) / 4) * 255;
	ocolor[2] *= ((1 + sin(e->x + turb)) / 4 + (1 + cos(e->y + turb)) / 4) * 255;
	color.r = (unsigned int)ocolor[0];
	color.g = (unsigned int)ocolor[1];
	color.b = (unsigned int)ocolor[2];
	return (color);
}

t_color			stripe(t_env *e, t_obj *obj, float turb)
{
	t_color		 	color;
	float			ocolor[3];

	turb *= 0.2;
	ocolor[0] = (float)(obj->color.r) / 255;
	ocolor[1] = (float)(obj->color.g) / 255;
	ocolor[2] = (float)(obj->color.b) / 255;
	ocolor[0] *= (1 + sin(e->x + turb)) / 2 * 255;
	ocolor[1] *= (1 + sin(e->x + turb)) / 2 * 255;
	ocolor[2] *= (1 + sin(e->x + turb)) / 2 * 255;
	color.r = (unsigned int)ocolor[0];
	color.g = (unsigned int)ocolor[1];
	color.b = (unsigned int)ocolor[2];
	return (color);
}

void			choose_texture(t_ray_data *d, float turb)
{
	t_env			*e;

	e = get_env();
	if (!ft_strncmp(d->shorter->procedural, "marble", 6))
		d->shorter->color = stripe(e, d->shorter, turb);
	else if (!ft_strncmp(d->shorter->procedural, "stripe", 6))
		d->shorter->color = stripe(e, d->shorter, 0);
	else if (!ft_strncmp(d->shorter->procedural, "square", 6))
		d->shorter->color = square(e, d->shorter, 0);
	else if (!ft_strncmp(d->shorter->procedural, "perlin", 6))
		d->shorter->color = perlin(d->shorter->color, turb);
	else if (d->shorter->tex_surface)
	{
		SDL_LockSurface(d->shorter->tex_surface);
		d->shorter->color = get_pixel(d->shorter->tex_surface, (int)e->x,
			(int)e->y);
		SDL_UnlockSurface(d->shorter->tex_surface);
	}
}

float			smooth_noise(float x, float y)
{
	float	fractx;
	float	fracty;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	float	value;
	t_env	*e;

	e = get_env();
	fractx = x - (int)x;
	fracty = y - (int)y;
	x1 = ((int)x + NOISE_WIDTH) % NOISE_WIDTH;
	y1 = ((int)y + NOISE_HEIGHT) % NOISE_HEIGHT;
	x2 = (x1 + NOISE_WIDTH - 1) % NOISE_WIDTH;
	y2 = (y1 + NOISE_HEIGHT - 1) % NOISE_HEIGHT;
	value = 0;
	value += fractx * fracty * (float)e->noise[y1][x1] / MAX_INT;
	value += (1 - fractx) * fracty * (float)e->noise[y1][x2] / MAX_INT;
	value += fractx * (1 - fracty) * (float)e->noise[y2][x1] / MAX_INT;
	value += (1 - fractx) * (1 - fracty) * (float)e->noise[y2][x2] / MAX_INT;
	return (value);
}

float			turbulence(float x, float y, float size)
{
	float	value;
	float	initial_size;
	float	i;

	value = 0;
	initial_size = size;
	i = 0;
	while (size >= 1)
	{
		value += smooth_noise(x / size, y / size) * size;
		size /= 2;
		++i;
	}
	return (128.0 * value / initial_size);
}

void			generate_noise(t_env *e)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (NOISE_HEIGHT > 128 || NOISE_WIDTH > 128)
	{
		ft_putstr("NOISE_WIDTH or NOISE_HEIGHT too large :");
		ft_putstr(" use a value under 128\n");
		exit(2);
	}
	while (i < NOISE_HEIGHT)
	{
		while(j < NOISE_WIDTH)
		{
			e->noise[i][j] = rand();
			++j;
		}
		j = 0;
		++i;
	}}
