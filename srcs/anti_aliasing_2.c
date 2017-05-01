/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 22:12:23 by jrouilly          #+#    #+#             */
/*   Updated: 2014/03/27 22:12:31 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

t_color			aa_32(t_env *e, t_obj *obj, unsigned int deph)
{
	t_color		color;

	color = aa_4(e, obj, deph);
	e->y += 0.125;
	color = mix_color(color, aa_4(e, obj, deph));
	--color.e;
	e->y -= 0.125;
	return (color);
}

t_color			aa_64(t_env *e, t_obj *obj, unsigned int deph)
{
	t_color		color;

	color = aa_8(e, obj, deph);
	e->x += 0.125;
	color = mix_color(color, aa_8(e, obj, deph));
	--color.e;
	e->x -= 0.125;
	return (color);
}
