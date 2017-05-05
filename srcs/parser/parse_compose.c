/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_compose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <vcaquant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:08:30 by vcaquant          #+#    #+#             */
/*   Updated: 2017/05/04 23:50:31 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>

int		parse_item_compo(t_item *item, int i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	item->next = (t_item *)malloc(sizeof(t_item));
	item->next->setnb = 0;
	if (!ft_strncmp(item->set[i], "\"compose\"", 9))
	{
		while (++i < item->setnb)
		{
			if (k == 0)
			{
				if (ft_strcchr(item->set[i], '{', '\n') != NULL)
					k++;
			}
			if (ft_strcchr(item->set[i], ',', '\n') == NULL &&
				ft_strcchr(item->set[i], '{', '\n') == NULL && k == 0)
			{
				item->next->set[j] = item->set[i];
				item->next->setnb++;
				return (i);
			}
			else if (ft_strcchr(item->set[i], ',', '\n') == NULL &&
					ft_strcchr(item->set[i], '{', '\n') == NULL && k > 0)
				k--;
			item->next->set[j++] = item->set[i];
			item->next->setnb++;
		}
	}
	return (i);
}

t_obj	*add_compose(t_obj *obj)
{
	if (obj->compose != NULL)
	{
		if (obj->compose->next != NULL)
		{
			obj = obj->compose->next;
			while (obj->next != NULL)
				obj = obj->next;
			obj->next = new_obj();
			obj = obj->next;
		}
		else
		{
			obj->compose->next = new_obj();
			obj = obj->compose->next;
		}
	}
	else
	{
		obj->compose = new_obj();
		obj = obj->compose;
	}
	return (obj);
}

int		parse_compose(t_env *e, t_item *item, t_obj *obj, int i)
{
	int		j;

	obj = add_compose(obj);
	j = parse_item_compo(item, i);
	item = item->next;
	i = 0;
	while (++i < item->setnb)
		i = parse_compare(e, item, obj, i);
	obj->type = obj_gettype(item->set[0]);
	if (obj->type == 128)
		obj->cap2 = 1000;
	if (obj->type == GLASS)
		glass(obj);
	obj->func = get_func(obj->type, obj->negative);
	obj->normale = get_normale(obj->type);
	obj->base = new_base();
	if (obj->texture)
		load_texture(obj);
	if (obj->normalmap)
		load_normalmap(obj);
	return (j);
}
