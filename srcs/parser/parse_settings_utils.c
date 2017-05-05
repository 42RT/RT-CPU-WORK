/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:16:12 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/05 17:18:24 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdlib.h>

void	parse_set_cam(t_env *e, char *str)
{
	if (!ft_strncmp(str, "\"cam_pos_x\"", 11))
		e->set->cam->pos.x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam_pos_y\"", 11))
		e->set->cam->pos.y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam_pos_z\"", 11))
		e->set->cam->pos.z = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam_ang_x\"", 11))
		e->set->cam->ang.x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam_ang_y\"", 11))
		e->set->cam->ang.y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam_ang_z\"", 11))
		e->set->cam->ang.z = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam2_pos_x\"", 12))
		e->set->cam2->pos.x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam2_pos_y\"", 12))
		e->set->cam2->pos.y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam2_pos_z\"", 12))
		e->set->cam2->pos.z = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam2_ang_x\"", 12))
		e->set->cam2->ang.x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam2_ang_y\"", 12))
		e->set->cam2->ang.y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cam2_ang_z\"", 12))
		e->set->cam2->ang.z = ft_atof(get_value(str));
}

void	parse_other_setting(t_env *e, char *str)
{
	if (!ft_strncmp(str, "\"refract\"", 9))
		e->set->refract = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"fov\"", 5))
		e->set->fov = ft_abs(ft_atoi(get_value(str)));
	else if (!ft_strncmp(str, "\"name\"", 6))
	{
		free(e->set->name);
		e->set->name = ft_strdup(get_value(str));
	}
	else if (!ft_strncmp(str, "\"preview\"", 9))
		e->set->preview = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"progressive_display\"", 21))
		e->set->display |= (ft_atoi(get_value(str)) != 0);
	else if (!ft_strncmp(str, "\"random_renderer\"", 17))
		e->set->display |= ((ft_atoi(get_value(str)) != 0) << 1);
	else if (!ft_strncmp(str, "\"threads\"", 9))
		e->set->threads = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"verbose\"", 9))
		e->set->verbose = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"luminosity\"", 12))
		e->set->luminosity = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"contrast\"", 10))
		e->set->contrast = ft_atof(get_value(str));
	else
		ft_printf("\033[31m%s Not found\n\033[0m", str);
}

void	parse_set_focus(t_env *e, char *str)
{
	if (!ft_strncmp(str, "\"focus_dst\"", 11))
		e->set->focus_dst = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"focus_range\"", 13))
		e->set->focus_range = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"focus_k\"", 9))
		e->set->focus_k = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"focus\"", 7))
		e->set->focus = ft_atoi(get_value(str));
}
