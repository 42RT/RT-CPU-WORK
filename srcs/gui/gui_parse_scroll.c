/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_scroll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_parse_scroll_suite(t_scroll *scroll, char **tmp, char **tmp2)
{
	if (!ft_strcmp(tmp[0], "\t\ttag"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		scroll->tag = ft_strdup(tmp2[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		scroll->txt->content = ft_strdup(tmp2[1]);
	}
	else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
	{
		tmp2 = ft_strsplit(tmp[1], '"');
		scroll->txt->anchor = ft_strdup(tmp2[1]);
	}
	else
		gui_error(16);
	gui_free_array((void **)tmp2, 2);
}

t_scroll	*gui_parse_scroll(int fd, int nb)
{
	t_scroll	*scroll;
	char		**tmp;
	char		**tmp2;
	char		*line;
	int			i;

	tmp2 = NULL;
	scroll = gui_scroll_init();
	i = 0;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\t\tx"))
			scroll->dest.x = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ty"))
			scroll->dest.y = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
			scroll->txt->align = ft_atoi(tmp[1]);
		else
			gui_parse_scroll_suite(scroll, tmp, tmp2);
		gui_free_array((void **)tmp, 2);
		i++;
	}
	return (scroll);
}

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
			gui_free_array((void **)tmp, 2);
			free(lu);
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
	if ((lu = (char *)malloc(sizeof(char) * 10)) == NULL)
		error(1);
	fread(lu, sizeof(char), 10, GUI_SYS->output);
	lu_trim = ft_strdup_trim(lu);
	scroll->nb_value = ft_atoi(lu_trim);
	free(lu);
	free(lu_trim);
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
	scroll->nb_value = 6;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("0");
	value[1] = ft_strdup("2");
	value[2] = ft_strdup("4");
	value[3] = ft_strdup("8");
	value[4] = ft_strdup("16");
	value[5] = ft_strdup("32");
	if (e->set->aa == 0)
		scroll->active_value = 0;
	else
		scroll->active_value = log2(e->set->aa);
	scroll->mod = 0;
	return (value);
}

void	gui_get_16_9_10_suite(t_scroll *scroll, t_env *e)
{
	if (e->set->height == 2160)
		scroll->active_value = 8;
	else if (e->set->height == 1600)
		scroll->active_value = 7;
	else if (e->set->height == 1440)
		scroll->active_value = 6;
	else if (e->set->height == 1200)
		scroll->active_value = 5;
	else if (e->set->height == 1080)
		scroll->active_value = 4;
	else if (e->set->height == 1050)
		scroll->active_value = 3;
	else if (e->set->height == 720)
		scroll->active_value = 2;
	else if (e->set->height == 900)
		scroll->active_value = 1;
	else
		scroll->active_value = 0;
}

char	**gui_get_16_9_10(t_scroll *scroll, t_env *e)
{
	char	**value;

	scroll->nb_value = 9;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("1366x768");
	value[1] = ft_strdup("1440x900");
	value[2] = ft_strdup("1280x720");
	value[3] = ft_strdup("1680x1050");
	value[4] = ft_strdup("1920x1080");
	value[5] = ft_strdup("1920:1200");
	value[6] = ft_strdup("2560x1440");
	value[7] = ft_strdup("2560x1600");
	value[8] = ft_strdup("3840x2160");
	gui_get_16_9_10_suite(scroll, e);
	scroll->mod = 0;
	return (value);
}

void	gui_get_5_4_3_suite(t_scroll *scroll, t_env *e)
{
	if (e->set->height == 1536)
		scroll->active_value = 6;
	else if (e->set->height == 1200)
		scroll->active_value = 5;
	else if (e->set->height == 1050)
		scroll->active_value = 4;
	else if (e->set->height == 1024)
		scroll->active_value = 3;
	else if (e->set->height == 768)
		scroll->active_value = 2;
	else if (e->set->height == 600)
		scroll->active_value = 1;
	else
		scroll->active_value = 0;
}

char	**gui_get_5_4_3(t_scroll *scroll, t_env *e)
{
	char	**value;

	scroll->nb_value = 7;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("640x480");
	value[1] = ft_strdup("800x600");
	value[2] = ft_strdup("1024x768");
	value[3] = ft_strdup("1280x1024");
	value[4] = ft_strdup("1400x1050");
	value[5] = ft_strdup("1600x1200");
	value[6] = ft_strdup("2048x1536");
	gui_get_5_4_3_suite(scroll, e);
	scroll->mod = 0;
	return (value);
}

char	**gui_get_exotic_res(t_scroll *scroll, t_env *e)
{
	char	**value;

	scroll->nb_value = 3;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	value[0] = ft_strdup("42x42");
	value[1] = ft_strdup("1152x864");
	value[2] = ft_strdup("1600x1024");
	if (e->set->height == 1024)
		scroll->active_value = 2;
	else if (e->set->height == 864)
		scroll->active_value = 1;
	else
		scroll->active_value = 0;
	scroll->mod = 0;
	return (value);
}

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

char	**gui_get_scroll_texture_nml(t_scroll *scroll)
{
	DIR				*rep;
	struct dirent	*rfile;
	int				i;
	FILE			*sortie;
	char			*lu;
	char			*lu_trim;
	char			**value;
	char			**tmp;
	t_env			*e;
	t_gui			*gui;
	t_obj			*obj;

	rep = NULL;
	sortie = popen("find ./ressources/textures/*.bmp | wc -l", "r");
	if ((lu = (char *)malloc(sizeof(char) * 10)) == NULL)
		error(1);
	fread(lu, sizeof(char), 10, sortie);
	lu_trim = ft_strdup_trim(lu);
	scroll->nb_value = ft_atoi(lu_trim) + 1;
	free(lu);
	free(lu_trim);
	scroll->active_value = 0;
	scroll->mod = 0;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	if (!(rep = opendir("./ressources/textures")))
		gui_error(13);
	value[0] = ft_strdup("none");
	e = get_env();
	gui = get_gui();
	obj = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		obj = obj->next;
		i++;
	}
	i = 1;
	while ((rfile = readdir(rep)))
	{
		if (ft_strcmp(rfile->d_name, ".") && ft_strcmp(rfile->d_name, ".."))
		{
			tmp = ft_strsplit(rfile->d_name, '.');
			value[i++] = ft_strdup(tmp[0]);
			if (!ft_strcmp(value[i - 1], obj->texture))
				scroll->active_value = i - 1;
			free(tmp);
		}
	}
	if (closedir(rep) == -1)
		gui_error(14);
	return (value);
}

char	**gui_get_scroll_texture_pcd(t_scroll *scroll)
{
	char	**value;
	t_obj	*tmp;
	t_env	*e;
	t_gui	*gui;
	int		i;

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
	return (value);
}

char	**gui_get_scroll_texture_mtr(t_scroll *scroll)
{
	DIR				*rep;
	struct dirent	*rfile;
	int				i;
	FILE			*sortie;
	char			*lu;
	char			*lu_trim;
	char			**value;
	char			**tmp;
	t_env			*e;
	t_gui			*gui;
	t_obj			*obj;

	rep = NULL;
	sortie = popen("find ./ressources/normalmap/*.bmp | wc -l", "r");
	if ((lu = (char *)malloc(sizeof(char) * 10)) == NULL)
		error(1);
	fread(lu, sizeof(char), 10, sortie);
	lu_trim = ft_strdup_trim(lu);
	scroll->nb_value = ft_atoi(lu_trim) + 1;
	free(lu);
	free(lu_trim);
	scroll->active_value = 0;
	scroll->mod = 0;
	if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
		error(1);
	if (!(rep = opendir("./ressources/normalmap")))
		gui_error(13);
	value[0] = ft_strdup("none");
	e = get_env();
	gui = get_gui();
	obj = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		obj = obj->next;
		i++;
	}
	i = 1;
	while ((rfile = readdir(rep)))
	{
		if (ft_strcmp(rfile->d_name, ".") && ft_strcmp(rfile->d_name, ".."))
		{
			tmp = ft_strsplit(rfile->d_name, '.');
			value[i++] = ft_strdup(tmp[0]);
			if (!ft_strcmp(value[i - 1], obj->normalmap))
				scroll->active_value = i - 1;
			free(tmp);
		}
	}
	if (closedir(rep) == -1)
		gui_error(14);
	return (value);
}


char	**gui_get_scroll_value(t_scroll *scroll)
{
	char	**value;
	t_gui	*gui;
	t_env	*e;

	e = get_env();
	gui = get_gui();
	if (!ft_strcmp(scroll->tag, "SCN"))
		return (gui_get_scroll_scene(scroll, gui));
	else if (!ft_strcmp(scroll->tag, "OBJ"))
		return (gui_get_scroll_object(scroll, e));
	else if (!ft_strcmp(scroll->tag, "_AA"))
		return (gui_get_scroll_aa(scroll));
	else if (!ft_strcmp(scroll->tag, "RES"))
		return (gui_get_scroll_res(scroll));
	else if (!ft_strcmp(scroll->tag, "NML"))
		return (gui_get_scroll_texture_nml(scroll));
	else if (!ft_strcmp(scroll->tag, "PCD"))
		return (gui_get_scroll_texture_pcd(scroll));
	else if (!ft_strcmp(scroll->tag, "MTR"))
		return (gui_get_scroll_texture_mtr(scroll));
	else
	{
		scroll->nb_value = 10;
		scroll->active_value = 0;
		scroll->mod = 0;
		if (!(value = (char **)malloc(sizeof(char *) * scroll->nb_value)))
			error(1);
		value[0] = "valeur1";
		value[1] = "valeur2";
		value[2] = "valeur3";
		value[3] = "valeur4";
		value[4] = "valeur5";
		value[5] = "valeur6";
		value[6] = "valeur7";
		value[7] = "valeur8";
		value[8] = "valeur9";
		value[9] = "valeur10";
		return (value);
	}
}
