/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:13:01 by vcaquant          #+#    #+#             */
/*   Updated: 2017/05/04 22:13:06 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <parser.h>
#include <math.h>

void	parse_ang(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "\"x\"", 3))
		v->x = ((float)ft_atoi(get_value(str)) * M_PI_2) / 90;
	else if (!ft_strncmp(str, "\"y\"", 3))
		v->y = ((float)ft_atoi(get_value(str)) * M_PI_2) / 90;
	else if (!ft_strncmp(str, "\"z\"", 3))
		v->z = ((float)ft_atoi(get_value(str)) * M_PI_2) / 90;
}

void	parse_pos(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "\"x\"", 3))
		v->x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"y\"", 3))
		v->y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"z\"", 3))
		v->z = ft_atof(get_value(str));
}

void	parse_cap(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "\"cap1\"", 6))
		obj->cap1 = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cap2\"", 6))
		obj->cap2 = ft_atof(get_value(str));
}

int		parse_dis2(t_item *it, t_obj *o, int i, void (*f)(t_obj *, char *))
{
	while (ft_strchr(it->set[i + 1], ',') != NULL)
		f(o, it->set[++i]);
	f(o, it->set[++i]);
	return (i);
}
