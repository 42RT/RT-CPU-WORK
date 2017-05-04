/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 19:10:37 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 19:09:56 by vcaquant         ###   ########.fr       */
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

int		parse_dis(t_item *it, t_vector *v, int i, void (*f)(t_vector *, char *))
{
	while (ft_strchr(it->set[i + 1], ',') != NULL)
		f(v, it->set[++i]);
	f(v, it->set[++i]);
	return (i);
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
		else if (!ft_strncmp(item->set[i], "\"k1\"", 4))
			obj->k1 = ft_atof(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "\"k2\"", 4))
			obj->k2 = ft_atof(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "\"k3\"", 4))
			obj->k3 = ft_atof(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "\"type\"", 6))
			obj->type = light_type(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "\"mod\"", 5))
			obj->mod = ft_atof(get_value(item->set[i]));
	}
	add_light(e, obj);
}
