#include <gui.h>

void	gui_parse_window(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	printf("parsing WINDOW : ");
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tw"))
			gui->dest.w = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\th"))
			gui->dest.h = ft_atoi(tmp[1]);
		i++;
	}
	gui->dest.x = 0; //ALT_SCREEN_CENTERED + 800;
	gui->dest.y = SDL_WINDOWPOS_CENTERED;
	printf("OK (%d,%d)\n", gui->dest.w, gui->dest.h);
}

void	gui_parse_path(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	printf("parsing PATH : ");
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			PATH->texture = ft_strdup(tmp[1]);
		}
		if (!ft_strcmp(tmp[0], "\tfont"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			PATH->font = ft_strdup(tmp[1]);
		}
		i++;
	}
	printf("OK (%s,%s)\n", PATH->texture, PATH->font);
}

void	gui_parse_def_font(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	printf("parsing DEF FONT : ");
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tsize"))
			TTF->def_size = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tfont"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			TTF->def_ttf = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\tborder_step"))
			TTF->def_border_step = ft_atoi(tmp[1]);
		i++;
	}
	printf("OK (%d,%s,%d)\n", TTF->def_size, TTF->def_ttf, TTF->def_border_step);
}

void	gui_parse_def_textbox(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	printf("parsing DEF TXB : ");
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tw"))
			DEF->txb_w = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\th"))
			DEF->txb_h  = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->txb_texture = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\ttexture_selected"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->txb_texture_selected = tmp[1];
		}
		i++;
	}
	printf("OK (%d,%d,%s,%s)\n", DEF->txb_w, DEF->txb_h, DEF->txb_texture, DEF->txb_texture_selected);

}

void	gui_parse_def_scroll(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	printf("parsing DEF SCL : ");
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tw"))
			DEF->scl_w = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\th"))
			DEF->scl_h = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tmax_shown"))
			DEF->scl_max_shown = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\thead_texture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->scl_texture_head = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\tlist_texture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->scl_texture_list = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\tbutton_texture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->sclb_texture = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\tbutton_texture_selected"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->sclb_texture_selected = tmp[1];
		}
		i++;
	}
	printf("OK (%d,%d,%d,%s,%s,%s,%s)\n", DEF->scl_w, DEF->scl_h, DEF->scl_max_shown, DEF->scl_texture_head, DEF->scl_texture_list, DEF->sclb_texture, DEF->sclb_texture_selected);

}

void	gui_parse_def_button(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	printf("parsing DEF BTN : ");
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tw"))
			DEF->btn_w = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\th"))
			DEF->btn_h = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->btn_texture = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\ttexture_selected"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->btn_texture_selected = tmp[1];
		}
		i++;
	}
	printf("OK (%d,%d,%s,%s)\n", DEF->btn_w, DEF->btn_h, DEF->btn_texture, DEF->btn_texture_selected);

}

void	gui_parse_def_checkbox(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	i = 0;
	printf("parsing DEF CBX : ");
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tsize"))
			DEF->cbx_size = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ttexture"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->cbx_texture = tmp[1];
		}
		if (!ft_strcmp(tmp[0], "\ttexture_selected"))
		{
			tmp = ft_strsplit(tmp[1], '"');
			DEF->cbx_texture_selected = tmp[1];
		}
		i++;
	}
	printf("OK (%d,%s,%s)\n", DEF->cbx_size, DEF->cbx_texture, DEF->cbx_texture_selected);
}

void	gui_parse_help_builder(t_gui *gui, int fd, int nb)
{
	char	**tmp;
	int		i;
	char	*line;

	printf("parsing HELP menu : ");
	if ((HELP = (t_help *)malloc(sizeof(t_help))) == NULL)
		error(1);
	HELP->nature = HLP;
	HELP->active = 0;
	i = 0;
	while (i < nb)
	{
		get_next_line(fd, &line);
		tmp = ft_strsplit(line, ':');
		if (!ft_strcmp(tmp[0], "\tx"))
			HELP->dest.x = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\ty"))
			HELP->dest.y = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\tw"))
			HELP->dest.w = ft_atoi(tmp[1]);
		if (!ft_strcmp(tmp[0], "\th"))
			HELP->dest.h = ft_atoi(tmp[1]);
		i++;
	}
	printf("OK (%d,%d,%d,%d)\n", HELP->dest.x, HELP->dest.y, HELP->dest.w, HELP->dest.h);
}

void	gui_find_header(t_gui *gui, int fd, char *line)
{
	if (!ft_strcmp(line, "WINDOW:"))
		gui_parse_window(gui, fd, 2);
	else if (!ft_strcmp(line, "PATH:"))
		gui_parse_path(gui, fd, 2);
	else if (!ft_strcmp(line, "DEFAULT_FONT:"))
		gui_parse_def_font(gui, fd, 3);
	else if (!ft_strcmp(line, "DEFAULT_TEXTBOX:"))
		gui_parse_def_textbox(gui, fd, 4);
	else if (!ft_strcmp(line, "DEFAULT_SCROLL:"))
		gui_parse_def_scroll(gui, fd, 7);
	else if (!ft_strcmp(line, "DEFAULT_BUTTON:"))
		gui_parse_def_button(gui, fd, 4);
	else if (!ft_strcmp(line, "DEFAULT_CHECKBOX:"))
		gui_parse_def_checkbox(gui, fd, 3);
	else if (!ft_strcmp(line, "HELP MENU BUILDER:"))
		gui_parse_help_builder(gui, fd, 4);
	else if (!ft_strcmp(line, "PARAM MENU BUILDER:"))
		gui_parse_param_builder(gui, fd, 10);
	else if (!ft_strcmp(line, "MAIN BUILDER:"))
		gui_parse_main_builder(gui, fd, 10);
	else
		return;
}

void	gui_parse_builder(t_gui *gui, char *file)
{
	int		fd;
	char	*line;
	int		ret;

	gui->action = 0;
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			//printf("FIND :%s\n", line);
			gui_find_header(gui, fd, line);
		}
		close(fd);
	}
	else
		gui_error(9);
}
