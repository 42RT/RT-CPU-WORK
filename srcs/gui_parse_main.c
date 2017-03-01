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

	i = 0;
	if ((button = (t_button *)malloc(sizeof(t_button))) == NULL)
		error(1);
	if ((button->txt = (t_txt *)malloc(sizeof(t_txt))) == NULL)
		error(1);
	button->nature = BTN;
	button->surface = NULL;
	button->bmp = NULL;
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
			if ((button->action = (char *)malloc(sizeof(char) * 3)) == NULL)
				error(1);
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
	if ((button = (t_button **)malloc(sizeof(t_button *))) == NULL)
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

t_button	*gui_init_scroll_button()
{
	t_button	*button;

	if ((button = (t_button *)malloc(sizeof(t_button))) == NULL)
		error(1);
	button->nature = BTN;
	button->action = "scroll";
	button->surface = NULL;
	button->bmp = NULL;
	return (button);
}

t_scroll	*gui_parse_scroll(int fd, int nb)
{
	t_scroll	*scroll;
	char		**tmp;
	char		*line;
	int			i;

	i = 0;
	if ((scroll = (t_scroll *)malloc(sizeof(t_scroll))) == NULL)
		error(1);
	scroll->nature = SCL;
	scroll->surface = NULL;
	scroll->bmp = NULL;
	scroll->button = gui_init_scroll_button();
	if ((scroll->txt = (t_txt *)malloc(sizeof(t_txt))) == NULL)
		error(1);
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
			if ((scroll->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
				error(1);
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

char	**gui_get_scroll_value(int nb)
{
	char	**value;

	if ((value = (char **)malloc(sizeof(char *) * nb)) == NULL)
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

t_scroll	**gui_parse_container_scroll(int fd, int qt, int id)
{
	t_scroll	**scroll;
	char		*line;
	int			i;

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\tscroll:"))
		gui_error(12);
	if ((scroll = (t_scroll **)malloc(sizeof(t_scroll *))) == NULL)
		error(1);
	i = 0;
	while (i < qt)
	{
		printf("\tSCL : (%d) : ", i);
		scroll[i] = gui_parse_scroll(fd, 6);
		scroll[i]->p = id;
		scroll[i]->id = i;
		scroll[i]->nb_value = 10;
		scroll[i]->active_value = 0;
		scroll[i]->mod = 0;
		scroll[i]->value = gui_get_scroll_value(scroll[i]->nb_value);
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

void	gui_get_textbox_value(t_textbox *textbox)
{
	if ((textbox->value = (char *)malloc(sizeof(char))) == NULL)
		error(1);
	gui_textbox_get_len(textbox);
	gui_textbox_value_clear(textbox, textbox->maxlen);
}

t_textbox	*gui_parse_textbox(int fd, int nb)
{
	t_textbox	*textbox;
	char		**tmp;
	char		*line;
	int			i;

	i = 0;
	if ((textbox = (t_textbox *)malloc(sizeof(t_textbox))) == NULL)
		error(1);
	if ((textbox->txt = (t_txt *)malloc(sizeof(t_txt))) == NULL)
		error(1);
	textbox->nature = TXB;
	textbox->surface = NULL;
	textbox->bmp = NULL;
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
			if ((textbox->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
				error(1);
			textbox->tag = tmp[1];
		}
		else if (!ft_strcmp(tmp[0], "\t\tmin"))
			textbox->min = ft_atoi(tmp[1]);
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

	get_next_line(fd, &line);
	if (ft_strcmp(line, "\ttextbox:"))
		gui_error(12);
	if ((textbox = (t_textbox **)malloc(sizeof(t_textbox *))) == NULL)
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
		gui_textbox_set(textbox[i]);
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
	checkbox->selected = false;
}

t_checkbox	*gui_parse_checkbox(int fd, int nb)
{
	t_checkbox	*checkbox;
	char		**tmp;
	char		*line;
	int			i;

	i = 0;
	if ((checkbox = (t_checkbox *)malloc(sizeof(t_checkbox))) == NULL)
		error(1);
	if ((checkbox->txt = (t_txt *)malloc(sizeof(t_txt))) == NULL)
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
	if ((checkbox = (t_checkbox **)malloc(sizeof(t_checkbox *))) == NULL)
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
	if ((gui->container = (t_container **)malloc(sizeof(t_container *) * GUI_CONTAINER_TOTAL_NB)) == NULL)
		error(1);
	while (id < nb)
	{
		if ((CONTAINER = (t_container *)malloc(sizeof(t_container))) == NULL)
			error(1);
		if ((CONTAINER->txt = (t_txt *)malloc(sizeof(t_txt))) == NULL)
			error(1);
		CONTAINER->button = NULL;
		CONTAINER->scroll = NULL;
		CONTAINER->textbox = NULL;
		CONTAINER->checkbox = NULL;
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
