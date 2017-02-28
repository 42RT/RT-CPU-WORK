/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 07:15:11 by jrouilly          #+#    #+#             */
/*   Updated: 2014/11/28 07:15:12 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdio.h>

void		aff_obj(t_obj *obj)
{
	if (!obj)
		return ;
	printf("\ntype: %d\n", obj->type);
	printf("negative: %d\n", obj->negative);
	printf("pos_x: %f\n", obj->pos.x);
	printf("pos_y: %f\n", obj->pos.y);
	printf("pos_z: %f\n", obj->pos.z);
	printf("ang_x: %f\n", obj->ang.x);
	printf("ang_y: %f\n", obj->ang.y);
	printf("ang_z: %f\n", obj->ang.z);
	printf("exp_x: %f\n", obj->exp.x);
	printf("exp_y: %f\n", obj->exp.y);
	printf("exp_z: %f\n", obj->exp.z);
	printf("color: %x\n", obj->color);
	printf("color2: %x\n", obj->color2);
	printf("color3: %x\n", obj->color3);
	printf("color_refract: %x\n", obj->color_refract);
	printf("size: %d\n", obj->size);
	printf("mod: %f\n", obj->mod);
	printf("reflect_k: %f\n", obj->reflect_k);
	printf("refract_k: %f\n", obj->refract_k);
	printf("refract_ind: %f\n", obj->refract_ind);
}
