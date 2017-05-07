/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_scroll_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:25:43 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_get_scroll_texture_pcd_2(t_scroll *scroll, t_env *e, t_gui *gui)
{
	t_obj	*tmp;
	int		i;

	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	if (!ft_strcmp(tmp->procedural, "perlin"))
		scroll->active_value = 1;
	else if (!ft_strcmp(tmp->procedural, "square"))
		scroll->active_value = 2;
	else if (!ft_strcmp(tmp->procedural, "stripe"))
		scroll->active_value = 3;
	else if (!ft_strcmp(tmp->procedural, "marble"))
		scroll->active_value = 4;
	else
		scroll->active_value = 0;
	scroll->mod = 0;
}

char	**gui_get_scroll_texture_pcd(t_scroll *scroll)
{
	char	**value;
	t_env	*e;
	t_gui	*gui;

	scroll->nb_value = 5;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("none");
	value[1] = ft_strdup("perlin");
	value[2] = ft_strdup("square");
	value[3] = ft_strdup("stripe");
	value[4] = ft_strdup("marble");
	e = get_env();
	gui = get_gui();
	gui_get_scroll_texture_pcd_2(scroll, e, gui);
	return (value);
}

void	gui_get_scroll_texture_mtr_3(t_scroll *scroll, char **value, t_obj *obj)
{
	t_gui	*gui;
	char	**tmp;
	int		i;

	i = 1;
	gui = get_gui();
	while ((GUI_SYS->rfile = readdir(GUI_SYS->dir)))
	{
		if (CMP(GUI_SYS->rfile->d_name, ".")
		&& CMP(GUI_SYS->rfile->d_name, ".."))
		{
			tmp = ft_strsplit(GUI_SYS->rfile->d_name, '.');
			value[i++] = ft_strdup(tmp[0]);
			if (!ft_strcmp(value[i - 1], obj->normalmap))
				scroll->active_value = i - 1;
			gui_free_carray(&tmp, 2);
		}
	}
}

char	**gui_get_scroll_texture_mtr_2(t_scroll *scroll, t_env *e, t_gui *gui)
{
	char	**value;
	int		i;
	t_obj	*obj;

	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	if (!(GUI_SYS->dir = opendir("./ressources/normalmap")))
		gui_error(13);
	value[0] = ft_strdup("none");
	obj = e->obj;
	i = 0;
	while (gui->container[0]->scroll[1]->active_value > i++)
		obj = obj->next;
	gui_get_scroll_texture_mtr_3(scroll, value, obj);
	if (closedir(GUI_SYS->dir) == -1)
		gui_error(14);
	return (value);
}

char	**gui_get_scroll_texture_mtr(t_scroll *scroll)
{
	char			*lu;
	char			*lu_trim;
	t_env			*e;
	t_gui			*gui;

	gui = get_gui();
	e = get_env();
	GUI_SYS->output = popen("find ./ressources/normalmap/*.bmp | wc -l", "r");
	if ((lu = (char *)malloc(sizeof(char) * 10)) == NULL)
		error(1);
	fread(lu, sizeof(char), 10, GUI_SYS->output);
	lu_trim = ft_strdup_trim(lu);
	scroll->nb_value = ft_atoi(lu_trim) + 1;
	gui_free_str(&lu);
	gui_free_str(&lu_trim);
	scroll->active_value = 0;
	scroll->mod = 0;
	return (gui_get_scroll_texture_mtr_2(scroll, e, gui));
}
