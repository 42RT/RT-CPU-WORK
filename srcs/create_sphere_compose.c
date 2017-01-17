/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere_compose.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:12:22 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/17 13:45:53 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_obj	*create_sphere_compose(t_vec pos, t_color color, float r)
{
	t_obj	*obj;

	if ((obj = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		error(1);
	obj->type = 's';
	obj->vec1 = pos;
	obj->vec2 = pos;
	obj->r = r;
	obj->d1 = 0;
	obj->d2 = 0;
	obj->reflect = 0;
	obj->color_t = color;
	obj->textures = NULL;
	obj->compose = NULL;
	obj->next = NULL;
	return (obj);
}
