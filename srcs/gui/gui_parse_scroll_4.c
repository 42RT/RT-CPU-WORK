/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_scroll_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 00:14:18 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

char	**gui_get_scroll_res(t_scroll *scroll)
{
	t_gui	*gui;
	t_env	*e;
	float	ratio;

	e = get_env();
	gui = get_gui();
	ratio = (float)gui->display->w / (float)gui->display->h;
	if (ratio >= 1.599999)
		return (gui_get_16_9_10(scroll, e));
	else if (ratio < 1.500000)
		return (gui_get_5_4_3(scroll, e));
	else
		return (gui_get_exotic_res(scroll, e));
}

void	gui_get_scl_texture_nml_3(t_scroll *scroll, char **value, t_obj *obj)
{
	char	**tmp;
	int		i;
	t_gui	*gui;

	gui = get_gui();
	i = 1;
	while ((GUI_SYS->rfile = readdir(GUI_SYS->dir)))
	{
		if (ft_strcmp(GUI_SYS->rfile->d_name, ".")
		&& ft_strcmp(GUI_SYS->rfile->d_name, ".."))
		{
			tmp = ft_strsplit(GUI_SYS->rfile->d_name, '.');
			value[i++] = ft_strdup(tmp[0]);
			if (!ft_strcmp(value[i - 1], obj->texture))
				scroll->active_value = i - 1;
			gui_free_array((void **)tmp, 2);
		}
	}
}

char	**gui_get_scl_texture_nml_2(t_scroll *scroll, t_env *e, t_gui *gui)
{
	char	**value;
	t_obj	*obj;
	int		i;

	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	if (!(GUI_SYS->dir = opendir("./ressources/textures")))
		gui_error(13);
	value[0] = ft_strdup("none");
	obj = e->obj;
	i = 0;
	while (gui->container[0]->scroll[1]->active_value > i++)
		obj = obj->next;
	gui_get_scl_texture_nml_3(scroll, value, obj);
	if (closedir(GUI_SYS->dir) == -1)
		gui_error(14);
	return (value);
}

char	**gui_get_scroll_texture_nml(t_scroll *scroll)
{
	char			*lu;
	char			*lu_trim;
	t_env			*e;
	t_gui			*gui;

	e = get_env();
	gui = get_gui();
	GUI_SYS->output = popen("find ./ressources/textures/*.bmp | wc -l", "r");
	if ((lu = (char *)malloc(sizeof(char) * 10)) == NULL)
		error(1);
	fread(lu, sizeof(char), 10, GUI_SYS->output);
	lu_trim = ft_strdup_trim(lu);
	scroll->nb_value = ft_atoi(lu_trim) + 1;
	free(lu);
	free(lu_trim);
	scroll->active_value = 0;
	scroll->mod = 0;
	return (gui_get_scl_texture_nml_2(scroll, e, gui));
}
