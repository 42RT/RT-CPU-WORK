/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 22:12:23 by jrouilly          #+#    #+#             */
/*   Updated: 2014/03/27 22:12:31 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

/*
** Supersampling antialiasing
*/

unsigned int	mix_color(unsigned int c1, unsigned int c2)
{
	unsigned int	color;

	color = (((c1 & 0xFF) + (c2 & 0xFF)) / 2) & 0xFF;
	color += (((c1 & 0xFF00) + (c2 & 0xFF00)) / 2) & 0xFF00;
	color += (((c1 & 0xFF0000) + (c2 & 0xFF0000)) / 2) & 0xFF0000;
	return (color);
}

unsigned int	aa_2(t_env *e, t_obj *obj, unsigned int deph)
{
	unsigned int	color;

	color = compute_color(e, obj, deph);
	e->y += 0.5;
	color = mix_color(color, compute_color(e, obj, deph));
	e->y -= 0.5;
	return (color);
}

unsigned int	aa_4(t_env *e, t_obj *obj, unsigned int deph)
{
	unsigned int	color;

	color = aa_2(e, obj, deph);
	e->x += 0.5;
	color = mix_color(color, aa_2(e, obj, deph));
	e->x -= 0.5;
	return (color);
}

unsigned int	aa_8(t_env *e, t_obj *obj, unsigned int deph)
{
	unsigned int	color;

	color = aa_4(e, obj, deph);
	e->y += 0.25;
	color = mix_color(color, aa_4(e, obj, deph));
	e->y -= 0.25;
	return (color);
}

unsigned int	aa_16(t_env *e, t_obj *obj, unsigned int deph)
{
	unsigned int	color;

	color = aa_8(e, obj, deph);
	e->x += 0.25;
	color = mix_color(color, aa_8(e, obj, deph));
	e->x -= 0.25;
	return (color);
}
