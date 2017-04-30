#include <gui.h>

void	gui_parse_container_info(t_gui *gui, int fd, int id, int nb)
{
	char	**tmp;
	char	*line;
	int		i;

	i = 0;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tx"))
			CONTAINER->dest.x = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ty"))
			CONTAINER->dest.y = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tw"))
			CONTAINER->dest.w = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\th"))
			CONTAINER->dest.h = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ttxt"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			CONTAINER->txt->content = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\ttxt_anchor"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			CONTAINER->txt->anchor = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\ttxt_align"))
			CONTAINER->txt->align = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tbutton_qt"))
			CONTAINER->button_qt = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tscroll_qt"))
			CONTAINER->scroll_qt = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ttextbox_qt"))
			CONTAINER->textbox_qt = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tcheckbox_qt"))
			CONTAINER->checkbox_qt = ft_atoi(tmp[1]);
		i++;
	}
	if (CONTAINER->txt->align == -1)
	{
		free(CONTAINER->txt);
		CONTAINER->txt = NULL;
	}
}

t_button	*gui_parse_button(int fd, int nb)
{
	t_button	*button;
	char		**tmp;
	char		*line;
	int			i;

	button = gui_button_init();
	i = 0;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\t\tx"))
			button->dest.x = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\t\ty"))
			button->dest.y = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\t\taction"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			button->action = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\t\ttxt"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			button->txt->content = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			button->txt->anchor = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
			button->txt->align = ft_atoi(tmp[1]);
		i++;
	}
	return (button);
}

t_button	**gui_parse_container_button(int fd, int qt, int id)
{
	t_button	**button;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\tbutton:"))
		gui_error(12);
	if ((button = (t_button **)malloc(sizeof(t_button *) * qt)) == NULL)
		error(1);
	i = 0;
	while (i < qt)
	{
		printf("\tBTN : (%d) : ", i);
		button[i] = gui_parse_button(fd, 6);
		button[i]->p = id;
		button[i]->id = i;
		printf("(%d,%d,%s) [\"%s\",%s,%d]\n", button[i]->dest.x, button[i]->dest.y, button[i]->action, button[i]->txt->content, button[i]->txt->anchor, button[i]->txt->align);
		gui_button_set(button[i]);
		i++;
		if (i < qt)
		{
			get_next_line(fd, &line);
			if (ft_strcmp(line, "\t\t,"))
				gui_error(11);
		}
	}
	return (button);
}

t_scroll	*gui_parse_scroll(int fd, int nb)
{
	t_scroll	*scroll;
	char		**tmp;
	char		*line;
	int			i;

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
		else if (!ft_strcmp(tmp[0], "\t\ttag"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			scroll->tag = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\ttxt"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			scroll->txt->content = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			scroll->txt->anchor = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
			scroll->txt->align = ft_atoi(tmp[1]);
		i++;
	}
	return (scroll);
}

char	**gui_get_scroll_scene(t_scroll *scroll)
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

	e = get_env();
	rep = NULL;
	i = 0;
	sortie = popen("find ./scene/*.rts | wc -l", "r");
	if ((lu = (char *)malloc(sizeof(char) * 10)) == NULL)
		error(1);
	fread(lu, sizeof(char), 10, sortie);
	lu_trim = ft_strdup_trim(lu);
	scroll->nb_value = ft_atoi(lu_trim);
	free(lu);
	free(lu_trim);
	scroll->active_value = 0;
	scroll->mod = 0;
	if ((value = (char **)malloc(sizeof(char *) * scroll->nb_value)) == NULL)
		error(1);
	if (!(rep = opendir("./scene")))
		gui_error(13);
	while ((rfile = readdir(rep)))
	{
		if (ft_strcmp(rfile->d_name, ".") && ft_strcmp(rfile->d_name, ".."))
		{
			lu = ft_strjoin("scene/", rfile->d_name);
			if (!ft_strcmp(e->av[1], lu))
				scroll->active_value = i;
			tmp = ft_strsplit(rfile->d_name, '.');
			value[i++] = ft_strdup(tmp[0]);
			free(tmp);
		}
	}
	free(lu);
	if (closedir(rep) == -1)
		gui_error(14);
	return (value);
}

char	**gui_get_scroll_object(t_scroll *scroll)
{
	char	**value;
	t_env	*e;
	t_obj	*tmp;
	int		i;

	i = 0;
	scroll->nb_value = 1;
	e = get_env();
	tmp = e->obj->next;
	while (tmp)
	{
		scroll->nb_value += 1;
		tmp = tmp->next;
	}
	if ((value = (char **)malloc(sizeof(char *) * scroll->nb_value)) == NULL)
		error(1);
	tmp = e->obj;
	while (i < scroll->nb_value)
	{
		if (tmp->type == 1)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".sphere"));
		else if (tmp->type == 2)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".plan"));
		else if (tmp->type == 4)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".dplan"));
		else if (tmp->type == 8)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".cylinder"));
		else if (tmp->type == 16)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".cone"));
		else if (tmp->type == 32)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".disk"));
		else if (tmp->type == 64)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".square"));
		else if (tmp->type == 128)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".cube"));
		else if (tmp->type == 256)
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".paraboloid"));
		else
			value[i] = ft_strdup(ft_strjoin(ft_itoa(i + 1), ".unknown"));
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
	scroll->mod = 0;
	return (value);
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
	printf("%d : %d\n", gui->display->w, gui->display->h);
	printf("RATIO : %f\n", ratio);
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

	if (!ft_strcmp(scroll->tag, "SCN"))
		return (gui_get_scroll_scene(scroll));
	else if (!ft_strcmp(scroll->tag, "OBJ"))
		return (gui_get_scroll_object(scroll));
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

t_scroll	**gui_parse_container_scroll(int fd, int qt, int id)
{
	t_scroll	**scroll;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\tscroll:"))
		gui_error(12);
	if (!(scroll = (t_scroll **)malloc(sizeof(t_scroll *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		printf("\tSCL : (%d) : ", i);
		scroll[i] = gui_parse_scroll(fd, 6);
		scroll[i]->p = id;
		scroll[i]->id = i;
		scroll[i]->value = gui_get_scroll_value(scroll[i]);
		printf("(%d,%d,%s) [\"%s\",%s,%d]\n", scroll[i]->dest.x, scroll[i]->dest.y, scroll[i]->tag, scroll[i]->txt->content, scroll[i]->txt->anchor, scroll[i]->txt->align);
		gui_scroll_set(scroll[i]);
		i++;
		if (i < qt)
		{
			get_next_line(fd, &line);
			if (ft_strcmp(line, "\t\t,"))
				gui_error(11);
		}
	}
	return (scroll);
}

char	*gui_get_textbox_X(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->pos.x));
}

char	*gui_get_textbox_Y(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->pos.y));
}

char	*gui_get_textbox_Z(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->pos.z));
}

char	*gui_get_textbox_AX(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->ang.x / M_PI_2 * 90));
}

char	*gui_get_textbox_AY(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->ang.y / M_PI_2 * 90));
}

char	*gui_get_textbox_AZ(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->ang.z / M_PI_2 * 90));
}

char	*gui_get_textbox_R(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->color.r));
}

char	*gui_get_textbox_G(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->color.g));
}

char	*gui_get_textbox_B(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->color.b));
}

char	*gui_get_textbox_A(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->color.a));
}

char	*gui_get_textbox_RFR(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_ftoa(tmp->refract_ind, 3));
}

char	*gui_get_textbox_RFL(void)
{
	t_env	*e;
	t_gui	*gui;
	t_obj	*tmp;
	int		i;

	e = get_env();
	gui = get_gui();
	tmp = e->obj;
	i = 0;
	while (i < gui->container[0]->scroll[1]->active_value)
	{
		tmp = tmp->next;
		i++;
	}
	return (ft_itoa(tmp->reflect_k));
}

void	gui_get_textbox_value(t_textbox *textbox)
{
	t_env *e;

	e = get_env();
	gui_textbox_get_len(textbox);
	if (!ft_strcmp(textbox->tag, "__X"))
		textbox->value = gui_get_textbox_X();
	else if (!ft_strcmp(textbox->tag, "__Y"))
		textbox->value = gui_get_textbox_Y();
	else if (!ft_strcmp(textbox->tag, "__Z"))
		textbox->value = gui_get_textbox_Z();
	else if (!ft_strcmp(textbox->tag, "_AX"))
		textbox->value = gui_get_textbox_AX();
	else if (!ft_strcmp(textbox->tag, "_AY"))
		textbox->value = gui_get_textbox_AY();
	else if (!ft_strcmp(textbox->tag, "_AZ"))
		textbox->value = gui_get_textbox_AZ();
	else if (!ft_strcmp(textbox->tag, "__R"))
		textbox->value = gui_get_textbox_R();
	else if (!ft_strcmp(textbox->tag, "__G"))
		textbox->value = gui_get_textbox_G();
	else if (!ft_strcmp(textbox->tag, "__B"))
		textbox->value = gui_get_textbox_B();
	else if (!ft_strcmp(textbox->tag, "__A"))
		textbox->value = gui_get_textbox_A();
	else if (!ft_strcmp(textbox->tag, "RFR"))
		textbox->value = gui_get_textbox_RFR();
	else if (!ft_strcmp(textbox->tag, "RFL"))
		textbox->value = gui_get_textbox_RFL();
	else if (!ft_strcmp(textbox->tag, "CPX"))
		textbox->value = ft_itoa(e->set->cam->pos.x);
	else if (!ft_strcmp(textbox->tag, "CPY"))
		textbox->value = ft_itoa(e->set->cam->pos.y);
	else if (!ft_strcmp(textbox->tag, "CPZ"))
		textbox->value = ft_itoa(e->set->cam->pos.z);
	else if (!ft_strcmp(textbox->tag, "CAX"))
		textbox->value = ft_itoa(e->set->cam->ang.x);
	else if (!ft_strcmp(textbox->tag, "CAY"))
		textbox->value = ft_itoa(e->set->cam->ang.y);
	else if (!ft_strcmp(textbox->tag, "CAZ"))
		textbox->value = ft_itoa(e->set->cam->ang.z);
	else
		event_txb_value_clear(textbox, textbox->maxlen);
}

t_textbox	*gui_parse_textbox(int fd, int nb)
{
	t_textbox	*textbox;
	char		**tmp;
	char		*line;
	int			i;

	textbox = gui_textbox_init();
	i = 0;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\t\tx"))
			textbox->dest.x = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ty"))
			textbox->dest.y = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ttag"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			if (!(textbox->tag = (char *)malloc(sizeof(char) * 3)))
				error(1);
			textbox->tag = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\tmin"))
		{
			textbox->min = ft_atoi(tmp[1]);
			if (textbox->min >= 0)
				textbox->reserved = 0;
			else
				textbox->reserved = 1;
		}
		else if (!ft_strcmp(tmp[0], "\t\tmax"))
			textbox->max = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ttxt"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			textbox->txt->content = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			textbox->txt->anchor = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
			textbox->txt->align = ft_atoi(tmp[1]);
		i++;
	}
	return (textbox);
}

t_textbox	**gui_parse_container_textbox(int fd, int qt, int id)
{
	t_textbox	**textbox;
	char		*line;
	int			i;
	t_gui		*gui;

	gui = get_gui();
	get_next_line(fd, &line);
	if (ft_strcmp(line, "\ttextbox:"))
		gui_error(12);
	if (!(textbox = (t_textbox **)malloc(sizeof(t_textbox *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		printf("\tTXB : (%d) : ", i);
		textbox[i] = gui_parse_textbox(fd, 8);
		textbox[i]->p = id;
		textbox[i]->id = i;
		gui_get_textbox_value(textbox[i]);
		printf("(%d,%d,%s,%d,%d) [\"%s\",%s,%d]\n", textbox[i]->dest.x, textbox[i]->dest.y, textbox[i]->tag, textbox[i]->min, textbox[i]->max, textbox[i]->txt->content, textbox[i]->txt->anchor, textbox[i]->txt->align);
		gui_textbox_set(textbox[i], gui->dest);
		i++;
		if (i < qt)
		{
			get_next_line(fd, &line);
			if (ft_strcmp(line, "\t\t,"))
				gui_error(11);
		}
	}
	return (textbox);
}

void	gui_get_checkbox_state(t_checkbox *checkbox)
{
	checkbox->selected = 0;
}

t_checkbox	*gui_parse_checkbox(int fd, int nb)
{
	t_checkbox	*checkbox;
	char		**tmp;
	char		*line;
	int			i;

	i = 0;
	if (!(checkbox = (t_checkbox *)malloc(sizeof(t_checkbox))))
		error(1);
	if (!(checkbox->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	checkbox->nature = CBX;
	checkbox->surface = NULL;
	checkbox->bmp = NULL;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\t\tx"))
			checkbox->dest.x = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ty"))
			checkbox->dest.y = ft_atoi(tmp[1]);
		else if (!ft_strcmp(tmp[0], "\t\ttag"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			if ((checkbox->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
				error(1);
			checkbox->tag = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\ttxt"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			checkbox->txt->content = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			checkbox->txt->anchor = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
			checkbox->txt->align = ft_atoi(tmp[1]);
		i++;
	}
	return (checkbox);
}

t_checkbox	**gui_parse_container_checkbox(int fd, int qt)
{
	t_checkbox	**checkbox;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\tcheckbox:"))
		gui_error(10);
	if (!(checkbox = (t_checkbox **)malloc(sizeof(t_checkbox *) * qt)))
		error(1);
	i = 0;
	while (i < qt)
	{
		printf("\tCBX : (%d)\n", i);
		checkbox[i] = gui_parse_checkbox(fd, 6);
		gui_get_checkbox_state(checkbox[i]);
		i++;
		if (i < qt)
		{
			get_next_line(fd, &line);
			if (ft_strcmp(line, "\t\t,"))
				gui_error(11);
		}
	}
	return (checkbox);
}

void	gui_parse_main_builder(t_gui *gui, int fd, int nb)
{
	char	*line;
	int		id;

	id = 0;
	printf("parsing MAIN BUILDER : \n");
	if (!(gui->container = (t_container **)malloc(sizeof(t_container *) * GUI_CONTAINER_TOTAL_NB)))
		error(1);
	while (id < nb)
	{
		if (!(CONTAINER = (t_container *)malloc(sizeof(t_container))))
			error(1);
		if (!(CONTAINER->txt = (t_txt *)malloc(sizeof(t_txt))))
			error(1);
		CONTAINER->button = NULL;
		CONTAINER->scroll = NULL;
		CONTAINER->textbox = NULL;
		CONTAINER->checkbox = NULL;
		CONTAINER->gauge = NULL;
		CONTAINER->txt->content = NULL;
		CONTAINER->txt->anchor = NULL;
		CONTAINER->txt->align = -1;
		CONTAINER->nature = CNT;
		gui_parse_container_info(gui, fd, id, 11);
		printf("CONTAINER[%d] : (%d,%d,%d,%d,%d,%d,%d,%d)\n", id, CONTAINER->dest.x, CONTAINER->dest.y, CONTAINER->dest.w, CONTAINER->dest.h, CONTAINER->button_qt, CONTAINER->scroll_qt, CONTAINER->textbox_qt, CONTAINER->checkbox_qt);
		if (CONTAINER->button_qt > 0)
			BUTTON = gui_parse_container_button(fd, CONTAINER->button_qt, id);
		if (CONTAINER->scroll_qt > 0)
			SCROLL = gui_parse_container_scroll(fd, CONTAINER->scroll_qt, id);
		if (CONTAINER->textbox_qt > 0)
			TEXTBOX = gui_parse_container_textbox(fd, CONTAINER->textbox_qt, id);
		if (CONTAINER->checkbox_qt > 0)
			CHECKBOX = gui_parse_container_checkbox(fd, CONTAINER->checkbox_qt);
		get_next_line(fd, &line);
		if (ft_strcmp(line, "\t,"))
			gui_error(10);
		id++;
	}
}
