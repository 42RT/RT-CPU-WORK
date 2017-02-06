#include <rt.h>

char	*str_tolower(char *str)
{
	unsigned int	i;
	char	*tmp;

	i = 0;
	if ((tmp = (char *)malloc(sizeof(char) * 10)) == NULL)
		error(1);
	while (i < ft_strlen(str))
	{
		if (str[i] >= 65 && str[i] <= 90)
			tmp[i] = str[i] + 32;
		else
			tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	gui_button_selected(t_gui *gui, t_button *button)
{
	gui_font_init(gui, "Starjedi", TTF->def_size);
	gui_widget_draw_depth(button->dest, GUI_BUTTON_DEPTH, "red brick");
	gui_widget_write_txt(button, "red brick");
	TTF_CloseFont(TTF->font);
}

void	gui_button_create_all(t_gui *gui)
{
	int i;
	int id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->button == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->button_qt)
			{
				gui_widget_texture_get_bmp(BUTTON[i], "button_jade.bmp");
				gui_widget_display(BUTTON[i]);
				gui_widget_draw_depth(BUTTON[i]->dest, GUI_BUTTON_DEPTH, "white");
				i++;
			}
			id++;
		}
	}
}

void	gui_button_set_halign(t_button *button)
{
	t_gui	*gui;

	gui = get_gui();
	if (button->dest.x == GUI_ALIGN_LEFT)
		button->dest.x = 10;
	else if (button->dest.x == GUI_ALIGN_MID)
		button->dest.x = (GUI_WIDTH / 2) - (button->dest.w / 2);
	else if (button->dest.x == GUI_ALIGN_RIGHT)
		button->dest.x = GUI_WIDTH - (button->dest.w + 10);
	else
		button->dest.x = button->dest.x;
}

void	gui_button_set_valign(t_button *button)
{
	t_gui	*gui;

	gui = get_gui();
	if (button->dest.y == GUI_ALIGN_LEFT)
		button->dest.y = BLOCK[button->p]->dest.y;
	else if (button->dest.y == GUI_ALIGN_MID)
		button->dest.y = BLOCK[button->p]->dest.y 
		+ (BLOCK[button->p]->dest.h / 7);
	else if (button->dest.y == GUI_ALIGN_RIGHT)
		button->dest.y = BLOCK[button->p]->dest.y + BLOCK[button->p]->dest.h 
		- DEF->btn_h;
	else
		button->dest.y = button->dest.y;
}

void	gui_button_set(t_button *button)
{
	t_gui	*gui;

	gui = get_gui();
	button->dest.w = DEF->btn_w;
	button->dest.h = DEF->btn_h;
	gui_button_set_halign(button);
	gui_button_set_valign(button);
}

void	gui_button_build(t_gui *gui)
{
	gui_button_create_all(gui);
}
