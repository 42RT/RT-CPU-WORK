/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 06:55:02 by jrouilly          #+#    #+#             */
/*   Updated: 2014/11/28 06:55:02 by jrouilly         ###   ########.fr       */
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

t_obj		*new_obj(void)
{
	t_obj	*res;

	res = (t_obj *)malloc(sizeof(t_obj));
	if (!res)
		return (0);
	res->negative = 0;
	set_def_obj_pos(res);
	res->color = DEF_COLOR;
	res->color2 = DEF_COLOR2;
	res->color3 = DEF_COLOR3;
	res->color_refract = DEF_COLOR_REFR;
	res->size = DEF_SIZE;
	res->mod = DEF_MOD;
	res->reflect_k = DEF_REFLECT_K;
	res->refract_k = DEF_REFRACT_K;
	res->refract_ind = DEF_REFRACT_IND;
	res->next = 0;
	return (res);
}
