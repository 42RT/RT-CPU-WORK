/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_scroll_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/11 18:55:13 by rdieulan         ###   ########.fr       */
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
		if (GUI_SYS->rfile->d_name[0] != '.'
		&& ft_strstr(GUI_SYS->rfile->d_name, ".rts"))
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

char	*gui_get_scroll_object_3(t_obj *tmp, char *num)
{
	if (tmp->type == 64)
		return (ft_strjoin(num, ".square"));
	else if (tmp->type == 128)
		return (ft_strjoin(num, ".cube"));
	else if (tmp->type == 256)
		return (ft_strjoin(num, ".paraboloid"));
	else if (tmp->type == 512)
		return (ft_strjoin(num, ".glass"));
	else
		return (ft_strjoin(num, ".unknown"));
}

char	*gui_get_scroll_object_2(t_obj *tmp, int i)
{
	char	*num;
	char	*ret;

	num = ft_itoa(i + 1);
	if (tmp->type == 1)
		ret = ft_strjoin(num, ".sphere");
	else if (tmp->type == 2)
		ret = ft_strjoin(num, ".plan");
	else if (tmp->type == 4)
		ret = ft_strjoin(num, ".dplan");
	else if (tmp->type == 8)
		ret = ft_strjoin(num, ".cylinder");
	else if (tmp->type == 16)
		ret = ft_strjoin(num, ".cone");
	else if (tmp->type == 32)
		ret = ft_strjoin(num, ".disk");
	else
		ret = gui_get_scroll_object_3(tmp, num);
	gui_free_str(&num);
	return (ret);
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
		value[i] = gui_get_scroll_object_2(tmp, i);
		tmp = tmp->next;
		i++;
	}
	scroll->active_value = 0;
	scroll->mod = 0;
	return (value);
}
