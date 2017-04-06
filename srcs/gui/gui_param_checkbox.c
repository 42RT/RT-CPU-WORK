#include <gui.h>

t_checkbox	*gui_param_checkbox_init(void)
{
	t_checkbox	*checkbox;

	if ((checkbox = (t_checkbox *)malloc(sizeof(t_checkbox))) == NULL)
		error(1);
	if ((checkbox->txt = (t_txt *)malloc(sizeof(t_txt))) == NULL)
		error(1);
	checkbox->surface = NULL;
	checkbox->bmp = NULL;
	checkbox->nature = CBX;
	return (checkbox);
}

void	gui_param_checkbox_set_halign(t_checkbox *checkbox)
{
	t_gui *gui;

	gui = get_gui();
	if (checkbox->dest.x == GUI_ALIGN_LEFT)
		checkbox->dest.x = PARAM->dest.x;
	else if (checkbox->dest.x == GUI_ALIGN_MID)
		checkbox->dest.x = (PARAM->dest.w / 2) - (checkbox->dest.w / 2);
	else if (checkbox->dest.x == GUI_ALIGN_RIGHT)
		checkbox->dest.x = PARAM->dest.w - checkbox->dest.w;
	else
		checkbox->dest.x = checkbox->dest.x;
}

void	gui_param_checkbox_set(t_checkbox *checkbox)
{
	t_gui	*gui;

	gui = get_gui();
	checkbox->dest.w = DEF->cbx_size;
	checkbox->dest.h = DEF->cbx_size;
	gui_param_checkbox_set_halign(checkbox);
}

void	gui_param_checkbox_create_all(t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->checkbox_qt)
	{
		if (PARAM_CBX->selected == 1)
		{
			gui_widget_texture_get_bmp(PARAM_CBX, "checkbox_selected.bmp");
			gui_widget_display(PARAM_CBX);
			gui_widget_draw_in_line(PARAM_CBX->dest, 3, "teal");
			gui_widget_draw_in_line(PARAM_CBX->dest, 1, "black");
		}
		else
		{
			gui_widget_texture_get_bmp(PARAM_CBX, "textbox_white.bmp");
			gui_widget_display(PARAM_CBX);
			gui_widget_draw_in_line(PARAM_CBX->dest, 1, "black");
		}
		i++;
	}
}

void	gui_checkbox_get_state(t_checkbox *checkbox)
{
	t_env *e;

	e = get_env();
	if (!ft_strcmp(checkbox->tag, "PVW"))
		checkbox->selected = e->set->preview;
	else
		checkbox->selected = 0;
}

void	gui_param_checkbox_enable(t_gui *gui, t_checkbox *checkbox)
{
	if (WIDGET)
		event_widget_deselect(gui);
	WIDGET = checkbox;
	checkbox->selected = 1;
	gui_main_refresh(gui);
}

void	gui_param_checkbox_disable(t_gui *gui, t_checkbox *checkbox)
{
	WIDGET = NULL;
	checkbox->selected = 0;
	gui_main_refresh(gui);
}

void	gui_param_checkbox_toggle(t_gui *gui, t_checkbox *checkbox)
{
	if (checkbox->selected == 1)
		gui_param_checkbox_disable(gui, checkbox);
	else
		gui_param_checkbox_enable(gui, checkbox);
}
