/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_light.c                                        :+:      :+:    :+:   */
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

void		aff_light(t_light *light)
{
	if (!light)
		return ;
	printf("\ntype: %d\n", light->type);
	printf("pos_x: %f\n", light->pos.x);
	printf("pos_y: %f\n", light->pos.y);
	printf("pos_z: %f\n", light->pos.z);
	printf("ang_x: %f\n", light->ang.x);
	printf("ang_y: %f\n", light->ang.y);
	printf("ang_z: %f\n", light->ang.z);
	printf("color: %x\n", tcolor_to_int(light->color));
	printf("k1: %f\n", light->k1);
	printf("k2: %f\n", light->k2);
	printf("k3: %f\n", light->k3);
}
