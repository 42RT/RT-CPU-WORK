/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 16:13:22 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 14:12:47 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_color		calc_shadow(t_ray *ray, t_color cobj)
{
	t_color		color;

	color.r = KA * RA * cobj.r;
	color.g = KA * GA * cobj.g;
	color.b = KA * BA * cobj.b;
	if (color.r < RCOLOR.r)
		color.r = RCOLOR.r;
	if (color.g < RCOLOR.g)
		color.g = RCOLOR.g;
	if (color.b < RCOLOR.b)
		color.b = RCOLOR.b;
	return (color);
}

t_color		calc_color(t_ray *ray, t_color cobj, t_color clight, double angle)
{
	t_color		color;
	double		x;

	x = dot(VDIR, REFLECT);
	color.r = KA * RA * cobj.r + KD * (cobj.r * clight.r * angle) + KS * clight.r * pow(x, SPEC);
	color.g = KA * GA * cobj.g + KD * (cobj.g * clight.g * angle) + KS * clight.g * pow(x, SPEC);
	color.b = KA * BA * cobj.b + KD * (cobj.b * clight.b * angle) + KS * clight.b * pow(x, SPEC);
	if (color.r < RCOLOR.r)
		color.r = RCOLOR.r;
	if (color.g < RCOLOR.g)
		color.g = RCOLOR.g;
	if (color.b < RCOLOR.b)
		color.b = RCOLOR.b;
	return (color);
}
