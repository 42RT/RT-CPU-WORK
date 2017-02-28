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
			gui_param_scroll_set(PARAM_SCL);
			i++;
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
					if (!ft_strcmp(tmp[1], "false"))
						PARAM_CBX->selected = false;
					if (!ft_strcmp(tmp[1], "true"))
						PARAM_CBX->selected = true;
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
			gui_param_checkbox_set(PARAM_CBX);
			i++;
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
		i++;
	}
	PARAM->button = NULL;
	PARAM->scroll = NULL;
	PARAM->textbox = NULL;
	PARAM->checkbox = NULL;
	PARAM->active = 0;
	printf("OK (%d, %d, %d, %d, %d, %d, %d, %d)\n", PARAM->dest.x, PARAM->dest.y, PARAM->dest.w, PARAM->dest.h, PARAM->button_qt, PARAM->scroll_qt, PARAM->textbox_qt, PARAM->checkbox_qt);
	//if (PARAM->button_qt > 0)
	//	gui_parse_param_button();
	if (PARAM->scroll_qt > 0)
		gui_parse_param_scroll(gui, fd, PARAM->scroll_qt);
	//if (PARAM->textbox_qt > 0)
	//	gui_parse_param_textbox();
	if (PARAM->checkbox_qt > 0)
		gui_parse_param_checkbox(gui, fd, PARAM->checkbox_qt);
}
