#include <gui.h>

void		gui_apply_object(t_gui *gui)
{
	t_env	*e;
	t_obj	*tmp;
	int		i;

	e = get_env();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	//printf("POS.X : %s\n", gui->container[1]->textbox[0]->value);
	tmp->pos.x = ft_atoi(gui->container[1]->textbox[0]->value);
	//printf("POS.Y : %s\n", gui->container[1]->textbox[1]->value);
	tmp->pos.y = ft_atoi(gui->container[1]->textbox[1]->value);
	//printf("POS.Z : %s\n", gui->container[1]->textbox[2]->value);
	tmp->pos.z = ft_atoi(gui->container[1]->textbox[2]->value);
	//printf("ANG.X : %s\n", gui->container[2]->textbox[0]->value);
	tmp->ang.x = ft_atof(gui->container[2]->textbox[0]->value) * M_PI_2 / 90;
	//printf("ANG.Y : %s\n", gui->container[2]->textbox[1]->value);
	tmp->ang.y = ft_atof(gui->container[2]->textbox[1]->value) * M_PI_2 / 90;
	//printf("ANG.Z : %s\n", gui->container[2]->textbox[2]->value);
	tmp->ang.z = ft_atof(gui->container[2]->textbox[2]->value) * M_PI_2 / 90;
	//printf("RED : %s\n", gui->container[3]->textbox[0]->value);
	tmp->color.r = ft_atoi(gui->container[3]->textbox[0]->value);
	//printf("GREEN : %s\n", gui->container[3]->textbox[1]->value);
	tmp->color.g = ft_atoi(gui->container[3]->textbox[1]->value);
	//printf("BLUE : %s\n", gui->container[3]->textbox[2]->value);
	tmp->color.b = ft_atoi(gui->container[3]->textbox[2]->value);
	//printf("ALPHA : %s\n", gui->container[3]->textbox[3]->value);
	tmp->color.a = ft_atoi(gui->container[3]->textbox[3]->value);
	//printf("REFLECT : %s\n", gui->container[4]->textbox[0]->value);
	tmp->reflect_k = ft_atoi(gui->container[4]->textbox[0]->value);
	//printf("REFRACT : %s\n", gui->container[5]->textbox[0]->value);
	tmp->refract_ind = ft_atof(gui->container[5]->textbox[0]->value);
}

void		gui_apply_setting(t_gui *gui)
{
	t_env		*e;
	char	*ptr;
	char	**tab;

	e = get_env();
	tab = ft_strsplit(PARAM->scroll[0]->value[PARAM->scroll[0]->active_value], 'x');
	e->set->oldw = e->set->width;
	e->set->oldh = e->set->height;
	e->set->width = ft_atoi((const char *)tab[0]);
	e->set->height = ft_atoi((const char *)tab[1]);
	free(tab[0]);
	free(tab[1]);
	free(tab);
	ptr = ft_strdup(PARAM->scroll[1]->value[PARAM->scroll[1]->active_value]);
	e->set->aa = ft_atoi((const char *)ptr);
	free(ptr);
	e->set->deph = (unsigned int)(PARAM->gauge[0]->active_value + 1);
	e->set->fov = (unsigned int)PARAM->gauge[1]->active_value;
	e->set->preview = PARAM->checkbox[0]->selected;
	printf("PREVIEW : %d : %d\n", e->set->preview, PARAM->checkbox[0]->selected);
}
