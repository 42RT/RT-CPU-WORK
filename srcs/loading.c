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
#include <libxmlx.h>

t_img	*create_new_load_bar(t_gfx *gfx)
{
	t_img	*res;

	res = libxmlx_new_image(gfx, 204, 14);
	init_bar(res, 0xAA1010A0, 0x42000000);
	return (res);
}

void	init_bar(t_img *bar, unsigned int color, unsigned int background)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 14)
	{
		j = -1;
		while (++j < 204)
		{
			if (i == 0 || i == 13 || j == 0 || j == 203)
				libxmlx_pixel_put_to_image(bar, j, i, color);
			else
				libxmlx_pixel_put_to_image(bar, j, i, background);
		}
	}
}

void	change_percent(float percent, t_img *bar, unsigned int color,
						unsigned int background)
{
	static unsigned int	old = 0;
	unsigned int		nb;
	unsigned int		sav;

	nb = (unsigned int)percent;
	percent -= nb;
	nb <<= 1;
	if (old > nb)
	{
		init_bar(bar, 0xAA1010A0, 0x42000000);
		old = 0;
	}
	if (old == nb)
		return ;
	old = nb;
	sav = nb - 1;
	if (percent >= 0.5)
		++nb;
	while (nb-- > old)
		load_add_line(bar, nb, color);
	while (background && old > sav && ++sav < 200)
		load_add_line(bar, sav, background);
}

void	load_add_line(t_img *bar, unsigned int x, unsigned int color)
{
	x += 2;
	libxmlx_pixel_put_to_image(bar, x, 2, color);
	libxmlx_pixel_put_to_image(bar, x, 3, color);
	libxmlx_pixel_put_to_image(bar, x, 4, color);
	libxmlx_pixel_put_to_image(bar, x, 5, color);
	libxmlx_pixel_put_to_image(bar, x, 6, color);
	libxmlx_pixel_put_to_image(bar, x, 7, color);
	libxmlx_pixel_put_to_image(bar, x, 8, color);
	libxmlx_pixel_put_to_image(bar, x, 9, color);
	libxmlx_pixel_put_to_image(bar, x, 10, color);
	libxmlx_pixel_put_to_image(bar, x, 11, color);
}
