#include <rt.h>

t_checkbox	*gui_param_checkbox_init(void)
{
	t_checkbox	*checkbox;

	if ((checkbox = (t_checkbox *)malloc(sizeof(t_checkbox))) == NULL)
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
		checkbox->dest.x = (GUI_WIDTH / 2) - (checkbox->dest.w / 2);
	else if (checkbox->dest.x == GUI_ALIGN_RIGHT)
		checkbox->dest.x = GUI_WIDTH - checkbox->dest.w;
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
		if (PARAM_CBX->selected)
		{
			gui_widget_texture_get_bmp(PARAM_CBX, "checkbox_selected.bmp");
			gui_widget_display(PARAM_CBX);
			gui_widget_draw_in_line(PARAM_CBX->dest, 3, "teal");
			gui_widget_draw_in_line(PARAM_CBX->dest, 1, "black");
		}
		else
		{
			printf("%d %d %d %d\n", PARAM_CBX->dest.x, PARAM_CBX->dest.y, PARAM_CBX->dest.w, PARAM_CBX->dest.h);
			gui_widget_texture_get_bmp(PARAM_CBX, "textbox_white.bmp");
			gui_widget_display(PARAM_CBX);
			gui_widget_draw_in_line(PARAM_CBX->dest, 1, "black");
		}
		i++;
	}
}

void	gui_param_checkbox_enable(t_gui *gui, t_checkbox *checkbox)
{
	if (WIDGET)
		event_widget_deselect(gui);
	WIDGET = checkbox;
	checkbox->selected = true;
	gui_main_refresh(gui);
}

void	gui_param_checkbox_disable(t_gui *gui, t_checkbox *checkbox)
{
	WIDGET = NULL;
	checkbox->selected = false;
	gui_main_refresh(gui);
}

void	gui_param_checkbox_toggle(t_gui *gui, t_checkbox *checkbox)
{
	if (checkbox->selected)
		gui_param_checkbox_disable(gui, checkbox);
	else
		gui_param_checkbox_enable(gui, checkbox);
}
