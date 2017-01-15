/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:06:23 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/11 16:06:28 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdlib.h>

void	parse_object_other(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "size", 4))
		obj->size = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "mod", 3))
		obj->mod = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "reflect_k", 9))
		obj->reflect_k = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "refract_k", 9))
		obj->refract_k = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "refract_ind", 11))
		obj->refract_ind = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "negative", 8))
	{
		str = get_value(str);
		obj->negative = (!ft_strncmp(str, "1", 1)
						|| !ft_strncmp(str, "true", 4));
	}
}

void	parse_obj_exp(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "exp_x", 5))
		obj->exp.x = atof(get_value(str));
	else if (!ft_strncmp(str, "exp_y", 5))
		obj->exp.y = atof(get_value(str));
	else if (!ft_strncmp(str, "exp_z", 5))
		obj->exp.z = atof(get_value(str));
}

void	parse_obj_color(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "color2", 6))
		obj->color2 = get_color(get_value(str));
	else if (!ft_strncmp(str, "color3", 6))
		obj->color3 = get_color(get_value(str));
	else if (!ft_strncmp(str, "color_refract", 13))
		obj->color_refract = get_color(get_value(str));
	else if (!ft_strncmp(str, "color", 5))
		obj->color = get_color(get_value(str));
}
