/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:04:33 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/24 12:47:50 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>

int		obj_gettype(char *str)
{
	if (!ft_strncmp(str, "\"sphere\"", 8))
		return (SPHERE);
	else if (!ft_strncmp(str, "\"plan\"", 6))
		return (PLANE);
	else if (!ft_strncmp(str, "\"dplane\"", 8))
		return (DPLANE);
	else if (!ft_strncmp(str, "\"cylindre\"", 10))
		return (CYLINDER);
	else if (!ft_strncmp(str, "\"cone\"", 6))
		return (CONE);
	else if (!ft_strncmp(str, "\"disk\"", 6))
		return (DISK);
	else if (!ft_strncmp(str, "\"square\"", 8))
		return (SQUARE);
	else if (!ft_strncmp(str, "\"cube\"", 6))
		return (CUBE);
	else if (!ft_strncmp(str, "\"paraboloid\"", 13))
		return (PARABOLOID);
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
		else if (!ft_strncmp(item->set[i], "\"exp\"", 5))
		{
			while (ft_strchr(item->set[i + 1], ',') != NULL)
				parse_obj_exp(obj, item->set[++i]);
			parse_obj_exp(obj, item->set[++i]);
		}
		else if (!ft_strncmp(item->set[i], "\"color", 6))
			parse_obj_color(obj, item->set[i]);
		else
			parse_object_other(obj, item->set[i]);
	}
	obj->type = obj_gettype(item->type);
	if (obj->type == 128)
		obj->cap2 = 1000;
	if (obj->type == DPLANE && obj->color == 0x00ffff)
	{
		obj->def.x = 1;
		obj->def.z = 1;
	}
	obj->func = get_func(obj->type, obj->negative);
	obj->normale = get_normale(obj->type);
	obj->base = new_base();
	if (obj->type)
		add_obj(e, obj);
}
