/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 12:08:31 by rfriscca          #+#    #+#             */
/*   Updated: 2017/02/09 12:47:21 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void				get_spec(unsigned int *color, t_light light,
	t_vector v, t_env *e)
{
	float			angle;
	unsigned int	lcolor;
	t_vector		cam_to_light;

	lcolor = 0xffffff;
	cam_to_light = e->set->cam->pos;
	sub_vector(&cam_to_light, &light.pos);
	angle = vec_dot(&cam_to_light, &v);
	lcolor = color_attenuate(lcolor, powf(angle, SPEC));
	color_mix_k(color, lcolor, 100);
}

/*
** lcolor = light color
** ocolor = object color
*/

unsigned int		calc_color(float refangle, float angle,
		t_obj *obj, t_light *light)
{
	unsigned int	color;
	t_color			lcolor;
	t_color			ocolor;

	color = 0;
	ocolor.r = (float)((obj->color >> 16) & 0xff) / 255;
	ocolor.g = (float)((obj->color >> 8) & 0xff) / 255;
	ocolor.b = (float)(obj->color & 0xff) / 255;
	lcolor.r = (float)((light->color >> 16) & 0xff);
	lcolor.g = (float)((light->color >> 8) & 0xff);
	lcolor.b = (float)(light->color & 0xff);
	ocolor.r = obj->coef_ambient * RAMBIENT * ocolor.r + obj->coef_diffuse *
		ocolor.r * lcolor.r * angle + lcolor.r * obj->coef_spec *
		pow(refangle, SPEC);
	ocolor.g = obj->coef_ambient * GAMBIENT * ocolor.g + obj->coef_diffuse *
		ocolor.g * lcolor.g * angle + lcolor.g * obj->coef_spec *
		pow(refangle, SPEC);
	ocolor.b = obj->coef_ambient * BAMBIENT * ocolor.b + obj->coef_diffuse *
		ocolor.b * lcolor.b * angle + lcolor.b * obj->coef_spec *
		pow(refangle, SPEC);
	color += (unsigned int)ocolor.r << 16;
	color += (unsigned int)ocolor.g << 8;
	color += (unsigned int)ocolor.b;
	return (color);
}

unsigned int		shadow(unsigned int obj_color)
{
	unsigned int	color;
	float			objr;
	float			objg;
	float			objb;

	color = 0;
	objr = (float)((obj_color >> 16) & 0xff);
	objg = (float)((obj_color >> 8) & 0xff);
	objb = (float)(obj_color & 0xff);
	objr = COEFAMBIENT * RAMBIENT * objr / 255;
	objg = COEFAMBIENT * GAMBIENT * objg / 255;
	objb = COEFAMBIENT * BAMBIENT * objb / 255;
	color += (unsigned int)objr << 16;
	color += (unsigned int)objg << 8;
	color += (unsigned int)objb;
	return (color);
}
