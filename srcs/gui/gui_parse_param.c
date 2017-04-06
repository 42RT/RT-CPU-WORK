#include <gui.h>

void	gui_parse_param_scroll(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	int		j;
	char	*line;

	get_next_line(fd, &line);
	if (!ft_strcmp(line, "\tscroll:"))
	{
		if ((PARAM->scroll = (t_scroll **)malloc(sizeof(t_scroll *) * nb)) == NULL)
			error(1);
		i = 0;
		while (i < nb)
		{
			printf("\tSCL : (%d) : ", i);
			PARAM_SCL = gui_param_scroll_init();
			PARAM_SCL->id = i;
			PARAM_SCL->p = -1;
			j = 0;
			while (j < 6)
			{
				get_next_line(fd, &line);
				tmp = ft_strsplit(line, ':');
				if (!ft_strcmp(tmp[0], "\t\tx"))
					PARAM_SCL->dest.x = ft_atoi(tmp[1]);
				if (!ft_strcmp(tmp[0], "\t\ty"))
					PARAM_SCL->dest.y = ft_atoi(tmp[1]);
				if (!ft_strcmp(tmp[0], "\t\ttag"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_SCL->tag = tmp[1];
				}
				if (!ft_strcmp(tmp[0], "\t\ttxt"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_SCL->txt->content = tmp[1];
				}
				if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_SCL->txt->anchor = tmp[1];
				}
				if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
					PARAM_SCL->txt->align = ft_atoi(tmp[1]);
				j++;
			}
			printf("(%d,%d,%s) [\"%s\",%s,%d]\n", PARAM_SCL->dest.x, PARAM_SCL->dest.y, PARAM_SCL->tag, PARAM_SCL->txt->content, PARAM_SCL->txt->anchor, PARAM_SCL->txt->align);
			PARAM_SCL->value = gui_get_scroll_value(PARAM_SCL);
			gui_param_scroll_set(PARAM_SCL);
			i++;
			if (i < nb)
			{
				get_next_line(fd, &line);
				if (ft_strcmp(line, "\t\t,"))
					gui_error(11);
			}
		}
	}
	else
		gui_error(10); // scroll attendu dans le builder
}

void	gui_parse_param_checkbox(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	int		j;
	char	*line;

	get_next_line(fd, &line);
	if (!ft_strcmp(line, "\tcheckbox:"))
	{
		if ((PARAM->checkbox = (t_checkbox **)malloc(sizeof(t_checkbox *) * nb)) == NULL)
			error(1);
		i = 0;
		while (i < nb)
		{
			printf("\tCBX : (%d) : ", i);
			PARAM_CBX = gui_param_checkbox_init();
			PARAM_CBX->id = i;
			PARAM_CBX->p = -1;
			j = 0;
			while (j < 7)
			{
				get_next_line(fd, &line);
				tmp = ft_strsplit(line, ':');
				if (!ft_strcmp(tmp[0], "\t\tx"))
					PARAM_CBX->dest.x = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ty"))
					PARAM_CBX->dest.y = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ttag"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_CBX->tag = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\tselected"))
				{
					if (!ft_strcmp(tmp[1], " false"))
						PARAM_CBX->selected = 0;
					if (!ft_strcmp(tmp[1], " true"))
						PARAM_CBX->selected = 1;
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_CBX->txt->content = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_CBX->txt->anchor = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
					PARAM_CBX->txt->align = ft_atoi(tmp[1]);
				j++;
			}
			printf("(%d,%d,%s,%d) [\"%s\",%s,%d]\n", PARAM_CBX->dest.x, PARAM_CBX->dest.y, PARAM_CBX->tag, PARAM_CBX->selected, PARAM_CBX->txt->content, PARAM_CBX->txt->anchor, PARAM_CBX->txt->align);
			gui_checkbox_get_state(PARAM_CBX);
			gui_param_checkbox_set(PARAM_CBX);
			i++;
			if (i < nb)
			{
				get_next_line(fd, &line);
				if (ft_strcmp(line, "\t\t,"))
					gui_error(11);
			}
		}
	}
	else
		gui_error(10); // scroll attendu dans le builder
}

void	gui_parse_param_button(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	int		j;
	char	*line;

	get_next_line(fd, &line);
	if (!ft_strcmp(line, "\tbutton:"))
	{
		if (!(PARAM->button = (t_button **)malloc(sizeof(t_button *) * nb)))
			error(1);
		i = 0;
		while (i < nb)
		{
			printf("\tBTN : (%d) : ", i);
			PARAM_BTN = gui_param_button_init();
			PARAM_BTN->id = i;
			PARAM_BTN->p = -1;
			j = 0;
			while (j < 6)
			{
				get_next_line(fd, &line);
				tmp = ft_strsplit(line, ':');
				if (!ft_strcmp(tmp[0], "\t\tx"))
					PARAM_BTN->dest.x = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ty"))
					PARAM_BTN->dest.y = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\taction"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_BTN->action = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_BTN->txt->content = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_BTN->txt->anchor = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
					PARAM_BTN->txt->align = ft_atoi(tmp[1]);
				j++;
			}
			printf("(%d,%d,%s) [\"%s\",%s,%d]\n", PARAM_BTN->dest.x, PARAM_BTN->dest.y, PARAM_BTN->action, PARAM_BTN->txt->content, PARAM_BTN->txt->anchor, PARAM_BTN->txt->align);
			gui_button_set(PARAM_BTN);
			i++;
			if (i < nb)
			{
				get_next_line(fd, &line);
				if (ft_strcmp(line, "\t\t,"))
					gui_error(11);
			}
		}
	}
	else
		gui_error(10); // scroll attendu dans le builder
}

void	gui_parse_param_textbox(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	int		j;
	char	*line;

	get_next_line(fd, &line);
	if (!ft_strcmp(line, "\ttextbox:"))
	{
		if (!(PARAM->textbox = (t_textbox **)malloc(sizeof(t_textbox *) * nb)))
			error(1);
		i = 0;
		while (i < nb)
		{
			printf("\tTXB : (%d) : ", i);
			PARAM_TXB = gui_textbox_init();
			PARAM_TXB->id = i;
			PARAM_TXB->p = -1;
			j = 0;
			while (j < 8)
			{
				get_next_line(fd, &line);
				tmp = ft_strsplit(line, ':');
				if (!ft_strcmp(tmp[0], "\t\tx"))
					PARAM_TXB->dest.x = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ty"))
					PARAM_TXB->dest.y = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ttag"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_TXB->tag = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\tmin"))
					PARAM_TXB->min = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\tmax"))
					PARAM_TXB->max = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ttxt"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_TXB->txt->content = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_TXB->txt->anchor = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
					PARAM_TXB->txt->align = ft_atoi(tmp[1]);
				j++;
			}
			printf("(%d,%d,%s) [%d,%d,\"%s\",%s,%d]\n", PARAM_TXB->dest.x, PARAM_TXB->dest.y, PARAM_TXB->tag, PARAM_TXB->min, PARAM_TXB->max, PARAM_TXB->txt->content, PARAM_TXB->txt->anchor, PARAM_TXB->txt->align);
			gui_get_textbox_value(PARAM_TXB);
			gui_textbox_set(PARAM_TXB, PARAM->dest);
			i++;
			if (i < nb)
			{
				get_next_line(fd, &line);
				if (ft_strcmp(line, "\t\t,"))
					gui_error(11);
			}
		}
	}
	else
	{
		printf("|%s|\n", line);
		gui_error(10); // scroll attendu dans le builder
	}
}

void	gui_parse_param_gauge(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	int		j;
	char	*line;

	get_next_line(fd, &line);
	if (!ft_strcmp(line, "\tgauge:"))
	{
		if (!(PARAM->gauge = (t_gauge **)malloc(sizeof(t_gauge *) * nb)))
			error(1);
		i = 0;
		while (i < nb)
		{
			printf("\tGAU : (%d) : ", i);
			PARAM_GAU = gui_gauge_init();
			PARAM_GAU->id = i;
			PARAM_GAU->p = -1;
			j = 0;
			while (j < 8)
			{
				get_next_line(fd, &line);
				tmp = ft_strsplit(line, ':');
				if (!ft_strcmp(tmp[0], "\t\tx"))
					PARAM_GAU->dest.x = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ty"))
					PARAM_GAU->dest.y = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ttag"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_GAU->tag = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\tmin"))
					PARAM_GAU->min = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\tmax"))
					PARAM_GAU->max = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ttxt"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_GAU->txt->content = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt_anchor"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_GAU->txt->anchor = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt_align"))
					PARAM_GAU->txt->align = ft_atoi(tmp[1]);
				j++;
			}
			printf("(%d,%d,%s) [%d,%d,\"%s\",%s,%d]\n", PARAM_GAU->dest.x, PARAM_GAU->dest.y, PARAM_GAU->tag, PARAM_GAU->min, PARAM_GAU->max, PARAM_GAU->txt->content, PARAM_GAU->txt->anchor, PARAM_GAU->txt->align);
			gui_gauge_set(PARAM_GAU);
			gui_gauge_get_value(PARAM_GAU);
			i++;
			if (i < nb)
			{
				get_next_line(fd, &line);
				if (ft_strcmp(line, "\t\t,"))
					gui_error(11);
			}
		}
	}
	else
		gui_error(10); // scroll attendu dans le builder
}

void	gui_parse_param_freetxt(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	int		j;
	char	*line;

	get_next_line(fd, &line);
	if (!ft_strcmp(line, "\tfreetxt:"))
	{
		if (!(PARAM->freetxt = (t_freetxt **)malloc(sizeof(t_freetxt *) * nb)))
			error(1);
		i = 0;
		while (i < nb)
		{
			printf("\tFTT : (%d) : ", i);
			PARAM_FTT = gui_freetxt_init();
			PARAM_FTT->id = i;
			PARAM_FTT->p = -1;
			j = 0;
			while (j < 4)
			{
				get_next_line(fd, &line);
				tmp = ft_strsplit(line, ':');
				if (!ft_strcmp(tmp[0], "\t\tx"))
					PARAM_FTT->dest.x = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ty"))
					PARAM_FTT->dest.y = ft_atoi(tmp[1]);
				else if (!ft_strcmp(tmp[0], "\t\ttag"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_FTT->tag = tmp[1];
				}
				else if (!ft_strcmp(tmp[0], "\t\ttxt"))
				{
					tmp = ft_strsplit(tmp[1], '"');
					PARAM_FTT->txt->content = tmp[1];
				}
				j++;
			}
			printf("(%d,%d,%s) [\"%s\"]\n", PARAM_FTT->dest.x, PARAM_FTT->dest.y, PARAM_FTT->tag, PARAM_FTT->txt->content);
			gui_freetxt_set(PARAM_FTT, PARAM->dest);
			i++;
			if (i < nb)
			{
				get_next_line(fd, &line);
				if (ft_strcmp(line, "\t\t,"))
					gui_error(11);
			}
		}
	}
	else
		gui_error(10); // scroll attendu dans le builder
}

void	gui_parse_param_builder(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	printf("parsing PARAM BUILDER : ");
	if ((PARAM = (t_param *)malloc(sizeof(t_param))) == NULL)
		error(1);
	PARAM->nature = PRM;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tx"))
			PARAM->dest.x = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ty"))
			PARAM->dest.y = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tw"))
			PARAM->dest.w = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\th"))
			PARAM->dest.h = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tbutton_qt"))
			PARAM->button_qt = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tscroll_qt"))
			PARAM->scroll_qt = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ttextbox_qt"))
			PARAM->textbox_qt = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tcheckbox_qt"))
			PARAM->checkbox_qt = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tgauge_qt"))
			PARAM->gauge_qt = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tfreetxt_qt"))
			PARAM->freetxt_qt = ft_atoi(tmp[1]);
		i++;
		free(tmp);
	}
	PARAM->button = NULL;
	PARAM->scroll = NULL;
	PARAM->textbox = NULL;
	PARAM->checkbox = NULL;
	PARAM->gauge = NULL;
	PARAM->active = 0;
	printf("OK (%d, %d, %d, %d, %d, %d, %d, %d, %d, %d)\n", PARAM->dest.x, PARAM->dest.y, PARAM->dest.w, PARAM->dest.h, PARAM->button_qt, PARAM->scroll_qt, PARAM->textbox_qt, PARAM->checkbox_qt, PARAM->gauge_qt, PARAM->freetxt_qt);
	if (PARAM->button_qt > 0)
		gui_parse_param_button(gui, fd, PARAM->button_qt);
	if (PARAM->scroll_qt > 0)
		gui_parse_param_scroll(gui, fd, PARAM->scroll_qt);
	if (PARAM->textbox_qt > 0)
		gui_parse_param_textbox(gui, fd, PARAM->textbox_qt);
	if (PARAM->checkbox_qt > 0)
		gui_parse_param_checkbox(gui, fd, PARAM->checkbox_qt);
	if (PARAM->gauge_qt > 0)
		gui_parse_param_gauge(gui, fd, PARAM->gauge_qt);
	if (PARAM->freetxt_qt > 0)
		gui_parse_param_freetxt(gui, fd, PARAM->freetxt_qt);
}
