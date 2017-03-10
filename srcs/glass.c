/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 14:27:46 by rfriscca          #+#    #+#             */
/*   Updated: 2017/03/10 14:28:26 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <parser.h>

void	create_neg_plane(t_obj *obj)
{
	obj->compose = new_obj();
	obj->compose->type = PLANE;
	obj->compose->negative = 1;
	obj->compose->ang.x = -M_PI_2;
	obj->compose->func = get_func(obj->compose->type, obj->compose->negative);
	obj->compose->normale = get_normale(obj->compose->type);
}

void	create_base_cone(t_obj *obj)
{
	obj->next = new_obj();
	obj->next->type = CONE;
	obj->next->negative = 0;
	obj->next->size = 300;
	obj->next->cap1 = 400;
	obj->next->cap2 = 500;
	obj->next->color = obj->color;
	obj->next->refract_k = obj->refract_k;
	obj->next->reflect_k = obj->reflect_k;
	obj->next->refract_ind = obj->refract_ind;
	obj->next->func = get_func(obj->next->type, obj->next->negative);
	obj->next->normale = get_normale(obj->next->type);
}

void	create_disk(t_obj *obj)
{
	obj->next = new_obj();
	obj->next->type = DISK;
	obj->next->negative = 0;
	obj->next->size = 175;
	obj->next->pos.z = 400;
	obj->next->color = obj->color;
	obj->next->refract_k = obj->refract_k;
	obj->next->reflect_k = obj->reflect_k;
	obj->next->refract_ind = obj->refract_ind;
	obj->next->ang.x = -M_PI_2;
	obj->next->func = get_func(obj->next->type, obj->next->negative);
	obj->next->normale = get_normale(obj->next->type);
}

void	create_demi_sphere(t_obj *obj)
{
	obj->compose = new_obj();
	obj->compose->type = SPHERE;
	obj->compose->negative = 0;
	obj->compose->pos.x = 0;
	obj->compose->pos.y = 0;
	obj->compose->pos.z = -500;
	obj->compose->size = 500;
	obj->compose->func = get_func(obj->compose->type, obj->compose->negative);
	obj->compose->normale = get_normale(obj->compose->type);
	obj->compose->color = obj->color;
	obj->compose->refract_k = obj->refract_k;
	obj->compose->reflect_k = obj->reflect_k;
	obj->compose->refract_ind = obj->refract_ind;
	create_neg_plane(obj->compose);
	create_base_cone(obj->compose);
	create_disk(obj->compose->next);
}

void	glass(t_obj *obj)
{
	obj->size = 100;
	obj->cap1 = 0;
	obj->cap2 = 400;
	create_demi_sphere(obj);
}
