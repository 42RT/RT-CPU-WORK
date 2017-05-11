/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 19:10:37 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/11 12:16:40 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>
#include <stdlib.h>

int		light_type(char *str)
{
	if (!ft_strncmp(str, "spot", 4))
		return (SPOT);
	else if (!ft_strncmp(str, "global", 5))
		return (GLOBAL);
	else
		return (NONE);
}

void	add_light(t_env *e, t_light *obj)
{
	obj->next = e->light;
	e->light = obj;
}

int		parse_dis_rgb(t_item *it, t_color *c, int i,
	void (*f)(t_color *, char *))
{
	while (ft_strchr(it->set[i + 1], ',') != NULL)
		f(c, it->set[++i]);
	f(c, it->set[++i]);
	c->a = 255;
	c->e = 0;
	return (i);
}

void	parse_coef(t_light *obj, char *str)
{
	if (!ft_strncmp(str, "\"coef_ambient\"", 14))
		obj->coef_ambient = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"coef_diffuse\"", 14))
		obj->coef_diffuse = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"coef_spec\"", 11))
		obj->coef_spec = ft_atof(get_value(str));
}

void	parse_light(t_env *e, t_item *item)
{
	t_light	*obj;
	int		i;

	obj = new_light();
	i = -1;
	while (++i < item->setnb)
	{
		if (!ft_strncmp(item->set[i], "\"position\"", 10))
			i = parse_dis(item, &(obj->pos), i, (parse_pos));
		else if (!ft_strncmp(item->set[i], "\"angle\"", 7))
			i = parse_dis(item, &(obj->ang), i, (parse_ang));
		else if (!ft_strncmp(item->set[i], "\"color\"", 7))
			obj->color = get_color(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "\"type\"", 6))
			obj->type = light_type(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "\"mod\"", 5))
			obj->mod = ft_atof(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "\"rgb\"", 5))
			i = parse_dis_rgb(item, &(obj->color), i, (parse_rgb));
		else if (!ft_strncmp(item->set[i], "\"coef_", 6))
			parse_coef(obj, item->set[i]);
		else
			ft_printf("\033[31m%s Not found\n\033[0m", item->set[i]);
	}
	add_light(e, obj);
}
