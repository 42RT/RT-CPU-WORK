/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:06:23 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/05 17:15:42 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdlib.h>

void	parse_object_other(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "\"size\"", 6))
		obj->size = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"mod\"", 5))
		obj->mod = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"reflect_k\"", 11))
		obj->reflect_k = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"transparency\"", 11))
		obj->transparency = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"refract_ind\"", 13))
		obj->refract_ind = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"negative\"", 10))
	{
		str = get_value(str);
		obj->negative = (!ft_strncmp(str, "1", 1)
						|| !ft_strncmp(str, "true", 4));
	}
	else if (!ft_strncmp(str, "\"texture\"", 9))
		obj->texture = ft_strdup(get_value(str));
	else if (!ft_strncmp(str, "\"procedural\"", 12))
		obj->procedural = ft_strdup(get_value(str));
	else if (!ft_strncmp(str, "\"normalmap\"", 11))
		obj->normalmap = ft_strdup(get_value(str));
	else
		ft_printf("\033[31m%s Not found\n\033[0m", str);
}

void	parse_obj_exp(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "\"x\"", 3))
		v->x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"y\"", 3))
		v->y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"z\"", 3))
		v->z = ft_atof(get_value(str));
	else
	{
		ft_printf("Bad name in Exp\n");
		exit(EXIT_SUCCESS);
	}
}

void	parse_obj_color(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "\"color2\"", 8))
		obj->color2 = get_color(get_value(str));
	else if (!ft_strncmp(str, "\"color3\"", 8))
		obj->color3 = get_color(get_value(str));
	else if (!ft_strncmp(str, "\"color_refract\"", 15))
		obj->color_refract = get_color(get_value(str));
	else if (!ft_strncmp(str, "\"color\"", 7))
		obj->color = get_color(get_value(str));
}
