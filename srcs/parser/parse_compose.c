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

int 	parse_compose(t_env *e, t_item *item, t_obj *obj, int i)
{
	int		j;

	obj->compose = new_obj();
	j = parse_item_compo(item, i);
	item = item->next;
	i = 0;
	while (++i < item->setnb)
	{
		if (!ft_strncmp(item->set[i], "\"position\"", 10))
			i = parse_dis(item, &(obj->compose->pos), i, (parse_pos));
		else if (!ft_strncmp(item->set[i], "\"angle\"", 7))
			i = parse_dis(item, &(obj->compose->ang), i, (parse_ang));
		else if (!ft_strncmp(item->set[i], "\"exp\"", 5))
			i = parse_dis(item, &(obj->compose->exp), i, (parse_obj_exp));
		else if (!ft_strncmp(item->set[i], "\"color", 6))
			parse_obj_color(obj->compose, item->set[i]);
		else if (!ft_strncmp(item->set[i], "\"def\"", 5))
			i = parse_dis(item, &(obj->compose->def), i, (parse_pos));
		else if (!ft_strncmp(item->set[i], "\"cap\"", 5))
			i = parse_dis2(item, obj->compose, i, (parse_cap));
		else if (!ft_strncmp(item->set[i], "\"compose\"", 9))
			i = parse_compose(e, item, obj->compose, i);
		else
			parse_object_other(obj->compose, item->set[i]);
	}
	obj->compose->type = obj_gettype(item->set[0]);
	if (obj->compose->type == 128)
		obj->compose->cap2 = 1000;
	if (obj->compose->type == GLASS)
		glass(obj->compose);
	obj->compose->func = get_func(obj->compose->type, obj->compose->negative);
	obj->compose->normale = get_normale(obj->compose->type);
	obj->compose->base = new_base();
	if (obj->compose->texture)
		load_texture(obj->compose);
	if (obj->compose->normalmap)
		load_normalmap(obj->compose);
	return (j);
}
