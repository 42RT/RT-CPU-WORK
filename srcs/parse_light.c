/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 19:10:37 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/17 19:10:43 by jrouilly         ###   ########.fr       */
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
		if (!ft_strncmp(item->set[i], "pos", 3))
			parse_pos(&(obj->pos), item->set[i]);
		else if (!ft_strncmp(item->set[i], "ang", 3))
			parse_ang(&(obj->ang), item->set[i]);
		else if (!ft_strncmp(item->set[i], "color", 5))
			obj->color = get_color(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "k1", 2))
			obj->k1 = atof(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "k2", 2))
			obj->k2 = atof(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "k3", 2))
			obj->k3 = atof(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "type", 4))
			obj->type = light_type(get_value(item->set[i]));
		else if (!ft_strncmp(item->set[i], "mod", 4))
			obj->mod = atof(get_value(item->set[i]));
	}
	add_light(e, obj);
}
