/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/16 18:49:43 by jrouilly          #+#    #+#             */
/*   Updated: 2017/03/12 00:46:05 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <raytracer.h>

t_color				mod_light(t_color color, float dst, float coef2)
{
	float		coef;
	t_color		res;


	res.a = 0xFF;
	coef = (1 + coef2) / (dst / 100 + coef2);
	res.r = color.r * coef;
	res.g = color.g * coef;
	res.b = color.b * coef;
	return (res);
}

void			get_spec(t_color *color, t_light light,	t_vector v, t_env *e)
{
	float			angle;
	t_color			lcolor;
	t_vector		cam_to_light;

	*(int *)&lcolor = 0xFFFFFF;
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

/*t_color			calc_color(float refangle, float angle,
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
	/////////////////verifier calcul pour inclure hdr et simplifier plus haut
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
}*/

/*
** data.x = len = distance entre objet -> lumiere
** data.y = refangle = angle entre rayon reflechi + vecteur directeur
** data.z = angle = angle entre rayon lumiere + normale de l'objet
*/

t_color				calc_color(t_vector data, t_color color,
								t_obj *obj, t_light *light)
{
	t_color			newcolor;
	float			lcolor[3];
	float			ocolor[3];

	newcolor = void_tcolor();
	ocolor[0] = (float)(color.r) / 255;
	ocolor[1] = (float)(color.g) / 255;
	ocolor[2] = (float)(color.b) / 255;
	lcolor[0] = (float)(light->color.r);
	lcolor[1] = (float)(light->color.g);
	lcolor[2] = (float)(light->color.b);
	ocolor[0] = obj->coef_ambient * RAMBIENT * ocolor[0] + obj->coef_diffuse *
		ocolor[0] * lcolor[0] * data.z + lcolor[0] * obj->coef_spec *
		pow(data.y, SPEC);
	ocolor[1] = obj->coef_ambient * GAMBIENT * ocolor[1] + obj->coef_diffuse *
		ocolor[1] * lcolor[1] * data.z + lcolor[1] * obj->coef_spec *
		pow(data.y, SPEC);
	ocolor[2] = obj->coef_ambient * BAMBIENT * ocolor[2] + obj->coef_diffuse *
		ocolor[2] * lcolor[2] * data.z + lcolor[2] * obj->coef_spec *
		pow(data.y, SPEC);
	newcolor.r = (unsigned char)ocolor[0];
	newcolor.g = (unsigned char)ocolor[1];
	newcolor.b = (unsigned char)ocolor[2];
	return (newcolor);
}

t_color				shadow(t_color obj_color, t_vector data)
{
	t_color			color;
	float			objr;
	float			objg;
	float			objb;

	color = void_tcolor();
	objr = (float)obj_color.r;
	objg = (float)obj_color.g;
	objb = (float)obj_color.b;
	objr = COEFAMBIENT * RAMBIENT * objr / 255 * data.z;
	objg = COEFAMBIENT * GAMBIENT * objg / 255 * data.z;
	objb = COEFAMBIENT * BAMBIENT * objb / 255 * data.z;
	color.r = (unsigned char)objr;
	color.g = (unsigned char)objg;
	color.b = (unsigned char)objb;
	return (color);
}

/*t_color			shadow(t_color obj_color)
{
	t_color		color;
	int			tmp[3];

	color.e = 0;
	color.a = 0xFF;
	tmp[0] = (int)((float)(COEFAMBIENT * RAMBIENT * (int)obj_color.r) / 255.0); // mod pour enlever 255
	tmp[1] = (int)((float)COEFAMBIENT * GAMBIENT * (int)obj_color.g) / 255.0;
	tmp[2] = (int)((float)COEFAMBIENT * BAMBIENT * (int)obj_color.b) / 255.0;
	while (tmp[0] > 255 || tmp[1] > 255 || tmp[2] > 255)
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
	}
	color.r = tmp[0];
	color.g = tmp[0];
	color.b = tmp[0];
	return (color);
}*/
