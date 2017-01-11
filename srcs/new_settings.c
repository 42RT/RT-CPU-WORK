/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 07:05:07 by jrouilly          #+#    #+#             */
/*   Updated: 2017/01/11 16:59:04 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtdefs.h>
#include <rt.h>

static void	set_def_cam(t_settings *res)
{
	res->cam = (t_cam *)malloc(sizeof(t_cam));
	res->cam2 = (t_cam *)malloc(sizeof(t_cam));
	res->cam->pos.x = DEF_CAM_POSX;
	res->cam->pos.y = DEF_CAM_POSY;
	res->cam->pos.z = DEF_CAM_POSZ;
	res->cam->ang.x = DEF_CAM_ANGX;
	res->cam->ang.y = DEF_CAM_ANGY;
	res->cam->ang.z = DEF_CAM_ANGZ;
	res->cam2->pos.x = DEF_CAM2_POSX;
	res->cam2->pos.y = DEF_CAM2_POSY;
	res->cam2->pos.z = DEF_CAM2_POSZ;
	res->cam2->ang.x = DEF_CAM2_ANGX;
	res->cam2->ang.y = DEF_CAM2_ANGY;
	res->cam2->ang.z = DEF_CAM2_ANGZ;
	res->verbose = 0;
}

t_settings	*new_settings(void)
{
	t_settings	*res;

	res = (t_settings *)malloc(sizeof(t_settings));
	if (!res)
		return (0);
	res->width = DEF_IMG_WIDTH;
	res->height = DEF_IMG_HEIGHT;
	res->aa = DEF_AA;
	res->deph = DEF_DEPH;
	res->reflect = DEF_REFLECT;
	res->refract = DEF_REFRACT;
	res->fov = DEF_FOV;
	res->d3_mode = DEF_3D_MODE;
	res->d3_offset = DEF_3D_OFFSET;
	res->d3_conv = DEF_3D_CONV;
	res->name = ft_strdup(DEF_NAME);
	res->focus = DEF_FOCUS;
	res->focus_dst = DEF_FOCUS_DST;
	res->focus_range = DEF_FOCUS_RANGE;
	res->focus_k = DEF_FOCUS_K;
	res->preview = DEF_PREVIEW;
	res->display = DEF_DISPLAY;
	res->threads = DEF_THREADS;
	set_def_cam(res);
	return (res);
}
