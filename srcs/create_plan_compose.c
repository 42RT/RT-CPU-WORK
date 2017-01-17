/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plan_compose.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 13:41:59 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/17 13:45:44 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_obj	*create_plan_compose(t_vec pos, t_color color, t_vec n)
{
	t_obj	*obj;

	if ((obj = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		error(1);
	obj->type = 'p';
	obj->vec1 = pos;
	obj->vec2 = n;
	obj->r = 0;
	obj->reflect = 0;
	obj->d1 = 0;
	obj->d2 = 0;
	obj->color_t = color;
	obj->compose = NULL;
	obj->next = NULL;
	return (obj);
}
