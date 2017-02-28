/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 15:47:40 by rfriscca          #+#    #+#             */
/*   Updated: 2017/02/22 14:34:24 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	compose_obj(t_obj *obj, t_equation *eq)
{
	t_obj		*compose_first;
	t_vector	pos_save;
	t_vector	v_save;

	compose_first = obj->compose;
	while (obj->compose)
	{
		pos_save = eq->o;
		v_save = eq->v;
		if (obj->compose->negative == 1)
			(obj->compose->func)(obj->compose, eq);
		else
			(obj->compose->func)(obj->compose, eq->o, eq->v);
		eq->o = pos_save;
		eq->v = v_save;
		obj->compose = obj->compose->next;
	}
	obj->compose = compose_first;
}
