/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 03:18:24 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 03:18:25 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <gfx.h>
#include <raytracer.h>

t_img			*gfx_new_image(t_gfx *gfx, int res_x, int res_y)
{
	t_img	*res;
	int		i;
	int		size;

	(void)gfx;
	res = (t_img *)malloc(sizeof(t_img));
	if (!res)
		return (0);
	res->width = res_x;
	res->height = res_y;
	size = res_y * res_x;
	res->data = (t_color *)malloc(size * sizeof(t_color));
	if (!res->data)
		return (0);
	i = -1;
	while (++i < size)
		res->data[i] = int_to_tcolor(0);
	return ((void *)res);
}

void			gfx_destroy_image(t_img *img)
{
	if (img)
	{
		free(img->data);
		free(img);
	}
}

void			gfx_fill_image(t_img *img, unsigned int width,
								unsigned int height, t_color color)
{
	unsigned int	x;
	unsigned int	y;

	y = height;
	while (y--)
	{
		x = width;
		while (x--)
			img->data[img->width * y + x] = color;
	}
}
