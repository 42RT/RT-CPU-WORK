/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:16:12 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/11 16:16:13 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdlib.h>

void	parse_set_cam(t_env *e, char *str)
{
	if (!ft_strncmp(str, "cam_pos_x", 9))
		e->set->cam->pos.x = atof(get_value(str));
	else if (!ft_strncmp(str, "cam_pos_y", 9))
		e->set->cam->pos.y = atof(get_value(str));
	else if (!ft_strncmp(str, "cam_pos_z", 9))
		e->set->cam->pos.z = atof(get_value(str));
	else if (!ft_strncmp(str, "cam_ang_x", 9))
		e->set->cam->ang.x = atof(get_value(str));
	else if (!ft_strncmp(str, "cam_ang_y", 9))
		e->set->cam->ang.y = atof(get_value(str));
	else if (!ft_strncmp(str, "cam_ang_z", 9))
		e->set->cam->ang.z = atof(get_value(str));
	else if (!ft_strncmp(str, "cam2_pos_x", 10))
		e->set->cam2->pos.x = atof(get_value(str));
	else if (!ft_strncmp(str, "cam2_pos_y", 10))
		e->set->cam2->pos.y = atof(get_value(str));
	else if (!ft_strncmp(str, "cam2_pos_z", 10))
		e->set->cam2->pos.z = atof(get_value(str));
	else if (!ft_strncmp(str, "cam2_ang_x", 10))
		e->set->cam2->ang.x = atof(get_value(str));
	else if (!ft_strncmp(str, "cam2_ang_y", 10))
		e->set->cam2->ang.y = atof(get_value(str));
	else if (!ft_strncmp(str, "cam2_ang_z", 10))
		e->set->cam2->ang.z = atof(get_value(str));
}

void	parse_other_setting(t_env *e, char *str)
{
	if (!ft_strncmp(str, "refract", 7))
		e->set->refract = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "fov", 3))
		e->set->fov = ft_abs(ft_atoi(get_value(str)));
	else if (!ft_strncmp(str, "name", 4))
	{
		free(e->set->name);
		e->set->name = ft_strdup(get_value(str));
	}
	else if (!ft_strncmp(str, "preview", 7))
		e->set->preview = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "progressive_display", 19))
		e->set->display = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "threads", 7))
		e->set->threads = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "verbose", 7))
		e->set->verbose = ft_atoi(get_value(str));
}

void	parse_set_focus(t_env *e, char *str)
{
	if (!ft_strncmp(str, "focus_dst", 9))
		e->set->focus_dst = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "focus_range", 11))
		e->set->focus_range = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "focus_k", 7))
		e->set->focus_k = atof(get_value(str));
	else if (!ft_strncmp(str, "focus", 5))
		e->set->focus = ft_atoi(get_value(str));
}
