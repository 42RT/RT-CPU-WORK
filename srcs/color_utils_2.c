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

void			get_spec(t_color *color, t_light light,	t_vector v, t_env *e)
{
	float			angle;
	t_color			lcolor;
	t_vector		cam_to_light;

	lcolor.r = 0xFF;
	lcolor.g = 0xFF;
	lcolor.b = 0xFF;
	lcolor.a = 0xFF;
	lcolor.e = 0;
	cam_to_light = e->set->cam->pos;
	sub_vector(&cam_to_light, &light.pos);
	angle = vec_dot(&cam_to_light, &v);
	lcolor = color_attenuate(lcolor, powf(angle, SPEC));
//	*color = color_add_k(*color, lcolor, 0.4);
	color_mix_k(color, lcolor, 100);
}

/*
** lcolor = light color
** ocolor = object color
*/

t_color			calc_color(float refangle, float angle,
							t_obj *obj, t_light *light)
{
	t_color			lcolor;
	t_color			ocolor;

	ocolor.r = obj->color.r;
	ocolor.g = obj->color.g;
	ocolor.b = obj->color.b;
	ocolor.e = 0;
	ocolor.a = 255;
	lcolor.r = light->color.r;
	lcolor.g = light->color.g;
	lcolor.b = light->color.b;
	lcolor.e = 0;
	lcolor.a = 255;
	/////////////////verifier calcul pour include hdr et simplifier plus haut
	ocolor.r = (obj->coef_ambient * RAMBIENT * (int)ocolor.r + obj->coef_diffuse *
		(int)ocolor.r * (int)lcolor.r * angle + (int)lcolor.r * obj->coef_spec *
		pow(refangle, SPEC)) / 255;
	ocolor.g = (obj->coef_ambient * GAMBIENT * (int)ocolor.g + obj->coef_diffuse *
		(int)ocolor.g * (int)lcolor.g * angle + (int)lcolor.g * obj->coef_spec *
		pow(refangle, SPEC)) / 255;
	ocolor.b = (obj->coef_ambient * BAMBIENT * (int)ocolor.b + obj->coef_diffuse *
		(int)ocolor.b * (int)lcolor.b * angle + (int)lcolor.b * obj->coef_spec *
		pow(refangle, SPEC)) / 255;
	return (ocolor);
}

t_color			shadow(t_color obj_color)
{
	t_color		color;
	int			tmp[3];

	color.e = 0;
	color.a = 0xFF;
	tmp[0] = (int)((float)(COEFAMBIENT * RAMBIENT * (int)obj_color.r) / 255.0); // mod pour enlever 255
	tmp[1] = (int)((float)COEFAMBIENT * GAMBIENT * (int)obj_color.g) / 255.0;
	tmp[2] = (int)((float)COEFAMBIENT * BAMBIENT * (int)obj_color.b) / 255.0;
	/*while (tmp[0] > 255 || tmp[1] > 255 || tmp[2] > 255)
	{
		++color.e;
		tmp[0] >>= 1;
		tmp[1] >>= 1;
		tmp[2] >>= 1;
	}
	while ((tmp[0] < 128 && tmp[1] < 128 && tmp[2] < 128)
			&& (tmp[0] || tmp[1] || tmp[2]))
	{
		--color.e;
		tmp[0] <<= 1;
		tmp[1] <<= 1;
		tmp[2] <<= 1;
	}*/
	color.r = tmp[0];
	color.g = tmp[0];
	color.b = tmp[0];
	return (color);
}
