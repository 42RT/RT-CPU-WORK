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
#include <stdio.h>

void			choose_texture(t_ray_data *d, float turb)
{
	t_env			*e;

	e = get_env();
	if (!e->surface)
		e->surface = SDL_LoadBMP("textures/PoolWater.bmp");
	if (!ft_strncmp(d->shorter->texture, "marble", 6))
		d->shorter->color = stripe(e, d->shorter, turb);
	else if (!ft_strncmp(d->shorter->texture, "fire", 4))
		d->shorter->color = fire(turb);
	else if (!ft_strncmp(d->shorter->texture, "bricks", 6))
	{
		SDL_LockSurface(e->surface);
		if (e->surface == NULL)
		{
			ft_printf("Can't load bricks.bmp");
			exit(1);
		}
		d->shorter->color = get_pixel(e->surface, (int)e->x,
			(int)e->y);
		SDL_UnlockSurface(e->surface);
	}
}

unsigned int	fire(float turb)
{
	unsigned int 	color;
	t_color			ocolor;

	turb /= 255;
	color = 0;
	ocolor.r = 247 * turb;
	ocolor.g = 164 * turb;
	ocolor.b = 0;
	color += (unsigned int)ocolor.r << 16;
	color += (unsigned int)ocolor.g << 8;
	color += (unsigned int)ocolor.b;
	return (color);
}

unsigned int	skybox(float turb)
{
	unsigned int 	color;
	t_color			ocolor;

	turb /= 255;
	color = 0;
	ocolor.r = 70 + 185 * turb;
	ocolor.g = 190 + 65 * turb;
	ocolor.b = 255;
	color += (unsigned int)ocolor.r << 16;
	color += (unsigned int)ocolor.g << 8;
	color += (unsigned int)ocolor.b;
	return (color);
}

unsigned int	square(t_env *e, t_obj *obj, float turb)
{
	unsigned int 	color;
	t_color			ocolor;

	turb *= 0.3;
	color = 0;
	ocolor.r = (float)((obj->color >> 16) & 0xff) / 255;
	ocolor.g = (float)((obj->color >> 8) & 0xff) / 255;
	ocolor.b = (float)(obj->color & 0xff) / 255;
	ocolor.r *= ((1 + sin(e->x + turb)) / 4 + (1 + cos(e->y + turb)) / 4) * 255;
	ocolor.g *= ((1 + sin(e->x + turb)) / 4 + (1 + cos(e->y + turb)) / 4) * 255;
	ocolor.b *= ((1 + sin(e->x + turb)) / 4 + (1 + cos(e->y + turb)) / 4) * 255;
	color += (unsigned int)ocolor.r << 16;
	color += (unsigned int)ocolor.g << 8;
	color += (unsigned int)ocolor.b;
	return (color);
}

unsigned int	stripe(t_env *e, t_obj *obj, float turb)
{
	unsigned int 	color;
	t_color			ocolor;

	turb *= 0.2;
	color = 0;
	ocolor.r = (float)((obj->color >> 16) & 0xff) / 255;
	ocolor.g = (float)((obj->color >> 8) & 0xff) / 255;
	ocolor.b = (float)(obj->color & 0xff) / 255;
	ocolor.r *= (1 + sin(e->x + turb)) / 2 * 255;
	ocolor.g *= (1 + sin(e->x + turb)) / 2 * 255;
	ocolor.b *= (1 + sin(e->x + turb)) / 2 * 255;
	color += (unsigned int)ocolor.r << 16;
	color += (unsigned int)ocolor.g << 8;
	color += (unsigned int)ocolor.b;
	return (color);
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
	}
}
