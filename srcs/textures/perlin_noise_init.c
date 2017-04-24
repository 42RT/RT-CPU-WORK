/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:34:58 by rfriscca          #+#    #+#             */
/*   Updated: 2017/04/24 13:35:01 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

float			smooth_noise(float x, float y)
{
	t_smooth_noise	sm;
	float			value;
	t_env			*e;

	e = get_env();
	sm.fractx = x - (int)x;
	sm.fracty = y - (int)y;
	sm.x1 = ((int)x + NOISE_WIDTH) % NOISE_WIDTH;
	sm.y1 = ((int)y + NOISE_HEIGHT) % NOISE_HEIGHT;
	sm.x2 = (sm.x1 + NOISE_WIDTH - 1) % NOISE_WIDTH;
	sm.y2 = (sm.y1 + NOISE_HEIGHT - 1) % NOISE_HEIGHT;
	value = 0;
	value += sm.fractx * sm.fracty * (float)e->noise[sm.y1][sm.x1] / MAX_INT;
	value += (1 - sm.fractx) * sm.fracty * (float)e->noise[sm.y1][sm.x2] /
	MAX_INT;
	value += sm.fractx * (1 - sm.fracty) * (float)e->noise[sm.y2][sm.x1] /
	MAX_INT;
	value += (1 - sm.fractx) * (1 - sm.fracty) *
	(float)e->noise[sm.y2][sm.x2] / MAX_INT;
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
		while (j < NOISE_WIDTH)
		{
			e->noise[i][j] = rand();
			++j;
		}
		j = 0;
		++i;
	}
}
