/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 01:39:21 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 01:39:22 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <raytracer.h>

t_obj		*copy_obj_elem(t_obj *obj)
{
	t_obj	*res;

	res = (t_obj *)malloc(sizeof(t_obj));
	res->type = obj->type;
	res->func = obj->func;
	res->normale = obj->normale;
	res->negative = obj->negative;
	res->pos = obj->pos;
	res->ang = obj->ang;
	res->exp = obj->exp;
	res->color = obj->color;
	res->color2 = obj->color2;
	res->color3 = obj->color3;
	res->color_refract = obj->color_refract;
	res->size = obj->size;
	res->mod = obj->mod;
	res->reflect_k = obj->reflect_k;
	res->refract_k = obj->refract_k;
	res->refract_ind = obj->refract_ind;
	res->dst = obj->dst;
	return (res);
}

t_obj		*copy_obj(t_obj *obj)
{
	t_obj	*act;
	t_obj	*res;

	if (!obj)
		return (0);
	res = copy_obj_elem(obj);
	act = res;
	obj = obj->next;
	while (obj)
	{
		act->next = copy_obj_elem(obj);
		obj = obj->next;
		act = act->next;
	}
	return (res);
}

t_env		*copy_env(t_env *e)
{
	t_env *res;

	res = (t_env *)malloc(sizeof(t_env));
	res->gfx = e->gfx;
	res->load_bar = e->load_bar;
	res->set = e->set;
	res->obj = copy_obj(e->obj);
	res->neg_obj = e->neg_obj;
	res->light = e->light;
	res->x = e->x;
	res->y = e->y;
	res->ac = e->ac;
	res->av = e->av;
	res->last_dst = e->last_dst;
	return (res);
}
