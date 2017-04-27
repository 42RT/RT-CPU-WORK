/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_apply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_apply_numerical(t_gui *gui, t_obj *tmp)
{
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
}

void		gui_apply_object_suite(t_gui *gui, t_obj *tmp)
{
	if (!ft_strcmp(GUI_SCL_MTR_VALUE, "none"))
		tmp->normalmap = NULL;
	else
		tmp->normalmap = ft_strdup(GUI_SCL_MTR_VALUE);
	if (tmp->texture)
		load_texture(tmp);
	if (tmp->normalmap)
		load_normalmap(tmp);
}

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
	gui_apply_numerical(gui, tmp);
	if (!ft_strcmp(GUI_SCL_PCD_VALUE, "none"))
		tmp->procedural = NULL;
	else
		tmp->procedural = ft_strdup(GUI_SCL_PCD_VALUE);
	if (!ft_strcmp(GUI_SCL_NML_VALUE, "none"))
		tmp->texture = NULL;
	else
		tmp->texture = ft_strdup(GUI_SCL_NML_VALUE);

	gui_apply_object_suite(gui, tmp);
}

void		gui_apply_setting(t_gui *gui)
{
	t_env	*e;
	char	*ptr;
	char	**res;

	e = get_env();
	res = ft_strsplit(GUI_SCL_RES_VALUE, 'x');
	e->set->oldw = e->set->width;
	e->set->oldh = e->set->height;
	e->set->width = ft_atoi((const char *)res[0]);
	e->set->height = ft_atoi((const char *)res[1]);
	gui_free_array((void **)res, 2);
	ptr = ft_strdup(GUI_SCL_AA_VALUE);
	e->set->aa = ft_atoi((const char *)ptr);
	free(ptr);
	e->set->threads = PARAM->gauge[0]->active_value;
	e->set->deph = (unsigned int)(PARAM->gauge[1]->active_value + 1);
	e->set->fov = (unsigned int)PARAM->gauge[2]->active_value;
	e->set->cam->pos.x = ft_atof(PARAM->textbox[0]->value);
	e->set->cam->pos.y = ft_atof(PARAM->textbox[1]->value);
	e->set->cam->pos.z = ft_atof(PARAM->textbox[2]->value);
	e->set->cam->ang.x = ft_atof(PARAM->textbox[3]->value);
	e->set->cam->ang.y = ft_atof(PARAM->textbox[4]->value);
	e->set->cam->ang.z = ft_atof(PARAM->textbox[5]->value);
	e->set->preview = PARAM->checkbox[0]->selected;
}
