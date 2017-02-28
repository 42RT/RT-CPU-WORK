/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 23:16:16 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/22 14:42:06 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <libxmlx.h>
#include <raytracer.h>

void		trace_ray_lights(t_env *e, t_obj *obj, t_vector *o, t_vector *v)
{
	(void)e;
	if (obj->negative == 0 && obj->func)
		(obj->func)(obj, *o, *v);
	else
		obj->dst = 1e8;
}

void		trace_ray(t_env *e, t_obj *obj, t_vector *o, t_vector *v)
{
	(void)e;
	if (obj->func && obj->negative == 0)
		(obj->func)(obj, *o, *v);
	else
		obj->dst = 1e8;
}

void		change_cam(t_env *e)
{
	t_cam	*buff;

	if (!e->set->d3_mode)
		return ;
	buff = e->set->cam;
	e->set->cam = e->set->cam2;
	e->set->cam2 = buff;
}

void		blur_mod(t_env *e, int x, int y, unsigned int *color)
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
	color_mix_k(color, libxmlx_get_pixel_color(e->gfx->buff[e->gfx->act],
				x - 2, y - 2), 8 * k);
	color_mix_k(color, libxmlx_get_pixel_color(e->gfx->buff[e->gfx->act],
				x - 2, y), 7 * k);
	color_mix_k(color, libxmlx_get_pixel_color(e->gfx->buff[e->gfx->act],
				x, y - 2), 6 * k);
	color_mix_k(color, libxmlx_get_pixel_color(e->gfx->buff[e->gfx->act],
				x - 1, y - 1), 5 * k);
	color_mix_k(color, libxmlx_get_pixel_color(e->gfx->buff[e->gfx->act],
				x, y - 1), 4 * k);
	color_mix_k(color, libxmlx_get_pixel_color(e->gfx->buff[e->gfx->act],
				x - 1, y), 3 * k);
}

void		fill_pixel(t_env *e, t_obj *obj)
{
	unsigned int	color;

	if (e->set->aa >= 16)
		color = aa_16(e, obj, e->set->deph);
	else if (e->set->aa >= 8)
		color = aa_8(e, obj, e->set->deph);
	else if (e->set->aa >= 4)
		color = aa_4(e, obj, e->set->deph);
	else if (e->set->aa >= 2)
		color = aa_2(e, obj, e->set->deph);
	else
		color = compute_color(e, obj, e->set->deph);
	color |= 0xFF000000;
	libxmlx_pixel_put_to_image(e->gfx->buff[e->gfx->act],
								(int)e->x, (int)e->y, color);
}

int			*init_map(int nb)
{
	int		*res;
	int		i;

	res = (int *)malloc(nb * sizeof(int));
	i = -1;
	while (++i < nb)
		res[i] = 1;
	return (res);
}
