/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:37:56 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/06 02:37:57 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <gfx.h>
#include <raytracer.h>

void		blur_mod(t_env *e, int x, int y, t_color *color)
{
	float	k;

	if ((e->last_dst > e->set->focus_dst - e->set->focus_range
			&& e->last_dst < e->set->focus_dst + e->set->focus_range)
			|| !e->set->focus || (x > 2 && y > 2))
		return ;
	k = fabs(e->last_dst - e->set->focus_dst) - e->set->focus_range;
	k /= 10000;
	k *= e->set->focus_k;
	if (k > 5)
		k = 5;
	color_mix_k(color, gfx_get_pixel_color(e->gfx->buff[BUFF_NB],
				x - 2, y - 2), 8 * k);
	color_mix_k(color, gfx_get_pixel_color(e->gfx->buff[BUFF_NB],
				x - 2, y), 7 * k);
	color_mix_k(color, gfx_get_pixel_color(e->gfx->buff[BUFF_NB],
				x, y - 2), 6 * k);
	color_mix_k(color, gfx_get_pixel_color(e->gfx->buff[BUFF_NB],
				x - 1, y - 1), 5 * k);
	color_mix_k(color, gfx_get_pixel_color(e->gfx->buff[BUFF_NB],
				x, y - 1), 4 * k);
	color_mix_k(color, gfx_get_pixel_color(e->gfx->buff[BUFF_NB],
				x - 1, y), 3 * k);
}
