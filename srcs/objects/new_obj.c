/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 06:55:02 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/05 21:17:08 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <parser.h>
#include <rtdefs.h>

static void	set_def_obj_pos(t_obj *obj)
{
	obj->pos.x = DEF_OBJ_POSX;
	obj->pos.y = DEF_OBJ_POSY;
	obj->pos.z = DEF_OBJ_POSZ;
	obj->ang.x = DEF_OBJ_ANGX;
	obj->ang.y = DEF_OBJ_ANGY;
	obj->ang.z = DEF_OBJ_ANGZ;
	obj->exp.x = DEF_OBJ_EXPX;
	obj->exp.y = DEF_OBJ_EXPY;
	obj->exp.z = DEF_OBJ_EXPZ;
}

void		new_obj_extend(t_obj *res)
{
	res->reflect_k = MIN_REFLECT_K;
	res->transparency = MIN_REFRACT_K;
	res->refract_ind = MIN_REFRACT_IND;
	res->texture = NULL;
	res->procedural = NULL;
	res->normalmap = NULL;
	res->nm_surface = NULL;
	res->tex_surface = NULL;
	res->compose = 0;
	res->next = 0;
}

t_obj		*new_obj(void)
{
	t_obj	*res;

	if (!(res = (t_obj *)malloc(sizeof(t_obj))))
		error(1);
	res->negative = 0;
	set_def_obj_pos(res);
	res->color = int_to_tcolor(DEF_COLOR);
	res->color2 = int_to_tcolor(DEF_COLOR2);
	res->color3 = int_to_tcolor(DEF_COLOR3);
	res->color_refract = int_to_tcolor(DEF_COLOR_REFR);
	res->size = DEF_SIZE;
	res->mod = DEF_MOD;
	res->cap1 = DEF_CAP1;
	res->cap2 = DEF_CAP2;
	res->def.x = 0;
	res->def.y = 0;
	res->def.z = 0;
	res->coef_ambient = DEF_AMB;
	res->coef_diffuse = DEF_DIF;
	res->coef_spec = DEF_SPE;
	res->dst = 1e8;
	new_obj_extend(res);
	return (res);
}
