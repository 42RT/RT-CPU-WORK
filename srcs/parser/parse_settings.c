/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 03:45:28 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 16:03:34 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <rtdefs.h>
#include <parser.h>

int		get_3d_mode(char *str)
{
	if (!ft_strncmp(str, "none", 5) || !ft_strncmp(str, "none", 5))
		return (NONE);
	else if (!ft_strncmp(str, "interleaved", 11))
		return (INTERLEAVED);
	else if (!ft_strncmp(str, "side_to_side", 12)
				|| !ft_strncmp(str, "side2side", 9))
		return (INTERLEAVED);
	else
		return (NONE);
}

void	parse_set_3d(t_env *e, char *str)
{
	if (!ft_strncmp(str, "d3_mode", 7))
		e->set->d3_mode = get_3d_mode(get_value(str));
	else if (!ft_strncmp(str, "d3_offset", 9))
		e->set->d3_offset = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "d3_conv", 7))
		e->set->d3_conv = ft_atof(get_value(str));
}

void	parse_settings(t_env *e, t_item *item)
{
	int		i;

	i = -1;
	while (++i < item->setnb)
	{
		if (!ft_strncmp(item->set[i], "\"cam", 4))
			parse_set_cam(e, item->set[i]);
		else if (!ft_strncmp(item->set[i], "\"focus", 6))
			parse_set_focus(e, item->set[i]);
		else if (!ft_strncmp(item->set[i], "\"d3\"", 4))
			parse_set_3d(e, item->set[i]);
		else if (!ft_strncmp(item->set[i], "\"width\"", 7))
			e->set->width = ft_abs(ft_atoi(get_value(item->set[i])));
		else if (!ft_strncmp(item->set[i], "\"height\"", 8))
			e->set->height = ft_abs(ft_atoi(get_value(item->set[i])));
		else if (!ft_strncmp(item->set[i], "\"antialiasing\"", 14))
			e->set->aa = ft_abs(ft_atoi(get_value(item->set[i])));
		else if (!ft_strncmp(item->set[i], "\"deph\"", 6))
			e->set->deph = ft_abs(ft_atoi(get_value(item->set[i])));
		else if (!ft_strncmp(item->set[i], "\"reflect\"", 9))
			e->set->reflect = ft_abs(ft_atoi(get_value(item->set[i])));
		else if (!ft_strncmp(item->set[i], "\"luminosity\"", 12))
			e->set->luminosity = ft_atof(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "\"contrast\"", 10))
			e->set->contrast = ft_atof(get_value(item->set[i]));
		else
			parse_other_setting(e, item->set[i]);
	}
}
