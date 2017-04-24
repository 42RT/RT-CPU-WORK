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

t_color			skybox(float turb)
{
	t_color			color;
	float			ocolor[3];

	turb /= 255;
	ocolor[0] = 70 + 185 * turb;
	ocolor[1] = 190 + 65 * turb;
	ocolor[2] = 255;
	color.r = (unsigned int)ocolor[0];
	color.g = (unsigned int)ocolor[1];
	color.b = (unsigned int)ocolor[2];
	return (color);
}

t_color			perlin(t_color objcolor, float turb)
{
	t_color			color;

	turb /= 255;
	color.r = objcolor.r * turb;
	color.g = objcolor.g * turb;
	color.b = objcolor.b * turb;
	return (color);
}

t_color			square(t_obj *obj, float turb, int x, int y)
{
	t_color			color;
	float			ocolor[3];

	turb *= 0.3;
	ocolor[0] = (float)(obj->color.r) / 255;
	ocolor[1] = (float)(obj->color.g) / 255;
	ocolor[2] = (float)(obj->color.b) / 255;
	ocolor[0] *= ((1 + sin(x + turb)) / 4 + (1 + cos(y + turb)) / 4) * 255;
	ocolor[1] *= ((1 + sin(x + turb)) / 4 + (1 + cos(y + turb)) / 4) * 255;
	ocolor[2] *= ((1 + sin(x + turb)) / 4 + (1 + cos(y + turb)) / 4) * 255;
	color.r = (unsigned int)ocolor[0];
	color.g = (unsigned int)ocolor[1];
	color.b = (unsigned int)ocolor[2];
	return (color);
}

t_color			stripe(t_obj *obj, float turb, int x)
{
	t_color			color;
	float			ocolor[3];

	turb *= 0.2;
	ocolor[0] = (float)(obj->color.r) / 255;
	ocolor[1] = (float)(obj->color.g) / 255;
	ocolor[2] = (float)(obj->color.b) / 255;
	ocolor[0] *= (1 + sin(x + turb)) / 2 * 255;
	ocolor[1] *= (1 + sin(x + turb)) / 2 * 255;
	ocolor[2] *= (1 + sin(x + turb)) / 2 * 255;
	color.r = (unsigned int)ocolor[0];
	color.g = (unsigned int)ocolor[1];
	color.b = (unsigned int)ocolor[2];
	return (color);
}
