/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 07:22:21 by jrouilly          #+#    #+#             */
/*   Updated: 2014/11/28 07:22:21 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>

#include <stdio.h>

static void	aff_cam_settings(t_settings *set)
{
	printf("cam_pos_x: %f\n", set->cam->pos.x);
	printf("cam_pos_y: %f\n", set->cam->pos.y);
	printf("cam_pos_z: %f\n", set->cam->pos.z);
	printf("cam_ang_x: %f\n", set->cam->ang.x);
	printf("cam_ang_y: %f\n", set->cam->ang.y);
	printf("cam_ang_z: %f\n", set->cam->ang.z);
	printf("cam2_pos_x: %f\n", set->cam2->pos.x);
	printf("cam2_pos_y: %f\n", set->cam2->pos.y);
	printf("cam2_pos_z: %f\n", set->cam2->pos.z);
	printf("cam2_ang_x: %f\n", set->cam2->ang.x);
	printf("cam2_ang_y: %f\n", set->cam2->ang.y);
	printf("cam2_ang_z: %f\n", set->cam2->ang.z);
}

void		aff_settings(t_settings *set)
{
	ft_printf("\nscreen: %dx%d\n", set->width, set->height);
	ft_printf("antialiasing: %d\n", set->aa);
	ft_printf("deph: %d\n", set->deph);
	ft_printf("reflect: %d\n", set->reflect);
	ft_printf("refract: %d\n", set->refract);
	ft_printf("fov: %d\n", set->fov);
	ft_printf("3d_mode: %d\n", set->d3_mode);
	printf("3d_offset: %f\n", set->d3_offset);
	printf("3d_conv: %f\n", set->d3_conv);
	ft_printf("name: %s\n", set->name);
	ft_printf("focus: %d\n", set->focus);
	ft_printf("preview: %d\n", set->preview);
	ft_printf("display: %d\n", set->display);
	ft_printf("focus_dst: %d\n", set->focus_dst);
	ft_printf("focus_range: %d\n", set->focus_range);
	aff_cam_settings(set);
}
