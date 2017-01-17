/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:04:33 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/11 16:04:34 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>

int		obj_gettype(char *str)
{
	if (!ft_strncmp(str, "sphere", 6))
		return (SPHERE);
	else if (!ft_strncmp(str, "plane", 5))
		return (PLANE);
	else if (!ft_strncmp(str, "dplane", 6))
		return (DPLANE);
	else if (!ft_strncmp(str, "cylinder", 8))
		return (CYLINDER);
	else if (!ft_strncmp(str, "cone", 4))
		return (CONE);
	else if (!ft_strncmp(str, "disk", 4))
		return (DISK);
	else if (!ft_strncmp(str, "square", 6))
		return (SQUARE);
	else
		return (NONE);
}

void	add_obj(t_env *e, t_obj *obj)
{
	if (obj->negative)
	{
		obj->next = e->neg_obj;
		e->neg_obj = obj;
	}
	else
	{
		obj->next = e->obj;
		e->obj = obj;
	}
}

void	parse_object(t_env *e, t_item *item)
{
	t_obj	*obj;
	int		i;

	obj = new_obj();
	i = -1;
	while (++i < item->setnb)
	{
		if (!ft_strncmp(item->set[i], "pos", 3))
			parse_pos(&(obj->pos), item->set[i]);
		else if (!ft_strncmp(item->set[i], "ang", 3))
			parse_ang(&(obj->ang), item->set[i]);
		else if (!ft_strncmp(item->set[i], "exp", 3))
			parse_obj_exp(obj, item->set[i]);
		else if (!ft_strncmp(item->set[i], "color", 5))
			parse_obj_color(obj, item->set[i]);
		else
			parse_object_other(obj, item->set[i]);
	}
	obj->type = obj_gettype(item->type);
	//obj->func = get_func(obj->type);
	//obj->normale = get_normale(obj->type);
	obj->base = new_base();
	if (obj->type)
		add_obj(e, obj);
}
