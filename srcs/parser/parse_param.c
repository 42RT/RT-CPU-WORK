/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <vcaquant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:13:01 by vcaquant          #+#    #+#             */
/*   Updated: 2017/05/06 20:48:20 by vcaquant         ###   ########.fr       */
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
	else
	{
		ft_printf("Bad name in Angle\n");
		exit(EXIT_SUCCESS);
	}
}

void	parse_pos(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "\"x\"", 3))
		v->x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"y\"", 3))
		v->y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"z\"", 3))
		v->z = ft_atof(get_value(str));
	else
	{
		ft_printf("Bad name %s\n", str);
		exit(EXIT_SUCCESS);
	}
}

void	parse_cap(t_obj *obj, char *str)
{
	if (!ft_strncmp(str, "\"cap1\"", 6))
		obj->cap1 = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"cap2\"", 6))
		obj->cap2 = ft_atof(get_value(str));
	else
	{
		ft_printf("Bad name in Cap\n");
		exit(EXIT_SUCCESS);
	}
}

int		parse_dis2(t_item *it, t_obj *o, int i, void (*f)(t_obj *, char *))
{
	while (ft_strchr(it->set[i + 1], ',') != NULL)
		f(o, it->set[++i]);
	f(o, it->set[++i]);
	return (i);
}

int		parse_compare(t_env *e, t_item *item, t_obj *obj, int i)
{
	if (!ft_strncmp(item->set[i], "\"position\"", 10))
		i = parse_dis(item, &(obj->pos), i, (parse_pos));
	else if (!ft_strncmp(item->set[i], "\"angle\"", 7))
		i = parse_dis(item, &(obj->ang), i, (parse_ang));
	else if (!ft_strncmp(item->set[i], "\"exp\"", 5))
		i = parse_dis(item, &(obj->exp), i, (parse_obj_exp));
	else if (!ft_strncmp(item->set[i], "\"color", 6))
		parse_obj_color(obj, item->set[i]);
	else if (!ft_strncmp(item->set[i], "\"def\"", 5))
		i = parse_dis(item, &(obj->def), i, (parse_pos));
	else if (!ft_strncmp(item->set[i], "\"cap\"", 5))
		i = parse_dis2(item, obj, i, (parse_cap));
	else if (!ft_strncmp(item->set[i], "\"compose\"", 9))
		i = parse_compose(e, item, obj, i);
	else if (!ft_strncmp(item->set[i], "\"size\"", 6))
		obj->size = ft_atoi(get_value(item->set[i]));
	else if (!ft_strncmp(item->set[i], "\"mod\"", 5))
		obj->mod = ft_atof(get_value(item->set[i]));
	else
		parse_object_other(obj, item->set[i]);
	return (i);
}
