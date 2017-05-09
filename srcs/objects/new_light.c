/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 19:32:35 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/17 19:32:36 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <parser.h>
#include <rtdefs.h>

static void	set_def_light_pos(t_light *obj)
{
	obj->pos.x = DEF_LIGHT_POSX;
	obj->pos.y = DEF_LIGHT_POSY;
	obj->pos.z = DEF_LIGHT_POSZ;
	obj->ang.x = DEF_LIGHT_ANGX;
	obj->ang.y = DEF_LIGHT_ANGY;
	obj->ang.z = DEF_LIGHT_ANGZ;
}

t_light		*new_light(void)
{
	t_light	*res;

	if (!(res = (t_light *)malloc(sizeof(t_light))))
		error(1);
	set_def_light_pos(res);
	res->color = int_to_tcolor(DEF_LIGHT_COLOR);
	res->mod = DEF_LIGHT_MOD;
	res->k1 = DEF_LIGHT_K1;
	res->k2 = DEF_LIGHT_K2;
	res->k3 = DEF_LIGHT_K3;
	res->coef_ambient = DEF_AMB;
	res->coef_diffuse = DEF_DIF;
	res->coef_spec = DEF_SPE;
	res->next = 0;
	return (res);
}
