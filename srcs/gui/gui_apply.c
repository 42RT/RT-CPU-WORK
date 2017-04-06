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
	tmp->pos.x = ft_atoi(gui->container[1]->textbox[0]->value);
	tmp->pos.y = ft_atoi(gui->container[1]->textbox[1]->value);
	tmp->pos.z = ft_atoi(gui->container[1]->textbox[2]->value);
	tmp->ang.x = ft_atof(gui->container[2]->textbox[0]->value) * M_PI_2 / 90;
	tmp->ang.y = ft_atof(gui->container[2]->textbox[1]->value) * M_PI_2 / 90;
	tmp->ang.z = ft_atof(gui->container[2]->textbox[2]->value) * M_PI_2 / 90;
	tmp->color.r = ft_atoi(gui->container[3]->textbox[0]->value);
	tmp->color.g = ft_atoi(gui->container[3]->textbox[1]->value);
	tmp->color.b = ft_atoi(gui->container[3]->textbox[2]->value);
	tmp->color.a = ft_atoi(gui->container[3]->textbox[3]->value);
	tmp->reflect_k = ft_atoi(gui->container[4]->textbox[0]->value);
	tmp->refract_ind = ft_atof(gui->container[5]->textbox[0]->value);
	//free(tmp->procedural);
	//free(tmp->texture);
	if (!ft_strcmp(GUI_SCL_PCD_VALUE, "none"))
		tmp->procedural = NULL;
	else
		tmp->procedural = ft_strdup(GUI_SCL_PCD_VALUE);
	printf("%s\n", GUI_SCL_NML_VALUE);
	tmp->texture = ft_strdup(GUI_SCL_NML_VALUE);
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
	e->set->cam->pos.x = ft_atof(PARAM->textbox[0]->value);
	e->set->cam->pos.y = ft_atof(PARAM->textbox[1]->value);
	e->set->cam->pos.z = ft_atof(PARAM->textbox[2]->value);
	e->set->preview = PARAM->checkbox[0]->selected;
}
