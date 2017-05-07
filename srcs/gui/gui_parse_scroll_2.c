/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_scroll_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:35:00 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

char	**gui_get_scl_scn_suite(t_scroll *scroll, t_env *e, t_gui *gui, int i)
{
	char	**value;
	char	**tmp;
	char	*lu;

	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	if (!(GUI_SYS->dir = opendir("./scene")))
		gui_error(13);
	while ((GUI_SYS->rfile = readdir(GUI_SYS->dir)))
	{
		if (GUI_SYS->rfile->d_name[0] != '.')
		{
			lu = ft_strjoin("scene/", GUI_SYS->rfile->d_name);
			if (!ft_strcmp(e->scene, lu))
				scroll->active_value = i;
			tmp = ft_strsplit(GUI_SYS->rfile->d_name, '.');
			value[i++] = ft_strdup(tmp[0]);
			gui_free_carray(&tmp, 2);
			gui_free_str(&lu);
		}
	}
	if (closedir(GUI_SYS->dir) == -1)
		gui_error(14);
	return (value);
}

char	**gui_get_scroll_scene(t_scroll *scroll, t_gui *gui)
{
	char	*lu;
	char	*lu_trim;
	t_env	*e;

	e = get_env();
	GUI_SYS->output = popen("find ./scene/*.rts | wc -l", "r");
	if (!(lu = (char *)malloc(sizeof(char) * 10)))
		error(1);
	fread(lu, sizeof(char), 10, GUI_SYS->output);
	lu_trim = ft_strdup_trim(lu);
	scroll->nb_value = ft_atoi(lu_trim);
	gui_free_str(&lu);
	gui_free_str(&lu_trim);
	scroll->active_value = -1;
	scroll->mod = 0;
	return (gui_get_scl_scn_suite(scroll, e, gui, 0));
}

char	*gui_get_scroll_object_suite(t_obj *tmp, int i)
{
	if (tmp->type == 1)
		return (ft_strjoin(ft_itoa(i + 1), ".sphere"));
	else if (tmp->type == 2)
		return (ft_strjoin(ft_itoa(i + 1), ".plan"));
	else if (tmp->type == 4)
		return (ft_strjoin(ft_itoa(i + 1), ".dplan"));
	else if (tmp->type == 8)
		return (ft_strjoin(ft_itoa(i + 1), ".cylinder"));
	else if (tmp->type == 16)
		return (ft_strjoin(ft_itoa(i + 1), ".cone"));
	else if (tmp->type == 32)
		return (ft_strjoin(ft_itoa(i + 1), ".disk"));
	else if (tmp->type == 64)
		return (ft_strjoin(ft_itoa(i + 1), ".square"));
	else if (tmp->type == 128)
		return (ft_strjoin(ft_itoa(i + 1), ".cube"));
	else if (tmp->type == 256)
		return (ft_strjoin(ft_itoa(i + 1), ".paraboloid"));
	else if (tmp->type == 512)
		return (ft_strjoin(ft_itoa(i + 1), ".glass"));
	else
		return (ft_strjoin(ft_itoa(i + 1), ".unknown"));
}

char	**gui_get_scroll_object(t_scroll *scroll, t_env *e)
{
	char	**value;
	t_obj	*tmp;
	int		i;

	scroll->nb_value = 1;
	tmp = e->obj->next;
	while (tmp)
	{
		scroll->nb_value += 1;
		tmp = tmp->next;
	}
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	tmp = e->obj;
	i = 0;
	while (scroll->nb_value > i)
	{
		value[i] = gui_get_scroll_object_suite(tmp, i);
		tmp = tmp->next;
		i++;
	}
	scroll->active_value = 0;
	scroll->mod = 0;
	return (value);
}

char	**gui_get_scroll_aa(t_scroll *scroll)
{
	char	**value;
	t_env	*e;

	e = get_env();
	scroll->nb_value = 7;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("0");
	value[1] = ft_strdup("2");
	value[2] = ft_strdup("4");
	value[3] = ft_strdup("8");
	value[4] = ft_strdup("16");
	value[5] = ft_strdup("32");
	value[6] = ft_strdup("64");
	if (e->set->aa == 0)
		scroll->active_value = 0;
	else
		scroll->active_value = log2(e->set->aa);
	scroll->mod = 0;
	return (value);
}
