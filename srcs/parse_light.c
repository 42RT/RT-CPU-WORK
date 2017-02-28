/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 19:10:37 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/22 15:01:36 by vcaquant         ###   ########.fr       */
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

void	parse_light(t_env *e, t_item *item)
{
	t_light	*obj;
	int		i;

	obj = new_light();
	i = -1;
	while (++i < item->setnb)
	{
		if (!ft_strncmp(item->set[i], "\"position\"", 10))
		{
			while (ft_strchr(item->set[i + 1], ',') != NULL)
				parse_pos(&(obj->pos), item->set[++i]);
			parse_pos(&(obj->pos), item->set[++i]);
		}
		else if (!ft_strncmp(item->set[i], "\"angle\"", 7))
		{
			while (ft_strchr(item->set[i + 1], ',') != NULL)
				parse_ang(&(obj->ang), item->set[++i]);
			parse_ang(&(obj->ang), item->set[++i]);
		}
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
