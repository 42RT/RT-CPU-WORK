#include <libft.h>
#include <rtdefs.h>
#include <parser.h>

int 	parse_item_compo(t_item *item, int i)
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

int 	parse_compose(t_env *e, t_item *item, t_obj *obj, int i)
{
	int		j;

	obj = add_compose(obj);
	j = parse_item_compo(item, i);
	item = item->next;
	i = 0;
	while (++i < item->setnb)
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
		else
			parse_object_other(obj, item->set[i]);
	}
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
