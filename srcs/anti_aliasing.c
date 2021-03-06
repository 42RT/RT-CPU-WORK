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
** Mix_color have to be reworked for 36/64 bits colors
*/

t_color			aa_2(t_env *e, t_obj *obj, unsigned int deph)
{
	t_color		color;

	color = compute_color(e, obj, deph);
	e->y += 0.5;
	color = mix_color(color, compute_color(e, obj, deph));
	--color.e;
	e->y -= 0.5;
	return (color);
}

t_color			aa_4(t_env *e, t_obj *obj, unsigned int deph)
{
	t_color		color;

	color = aa_2(e, obj, deph);
	e->x += 0.5;
	color = mix_color(color, aa_2(e, obj, deph));
	--color.e;
	e->x -= 0.5;
	return (color);
}

t_color			aa_8(t_env *e, t_obj *obj, unsigned int deph)
{
	t_color		color;

	color = aa_4(e, obj, deph);
	e->y += 0.25;
	color = mix_color(color, aa_4(e, obj, deph));
	--color.e;
	e->y -= 0.25;
	return (color);
}

t_color			aa_16(t_env *e, t_obj *obj, unsigned int deph)
{
	t_color		color;

	color = aa_8(e, obj, deph);
	e->x += 0.25;
	color = mix_color(color, aa_8(e, obj, deph));
	--color.e;
	e->x -= 0.25;
	return (color);
}
