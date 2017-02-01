#include <rt.h>

void	gui_param_checkbox_init(t_gui *gui, int nb)
{
	int i;

	if ((PARAM->checkbox = (t_checkbox **)malloc(sizeof(t_checkbox *) * nb)) == NULL)
		error(1);
	PARAM->checkbox_qt = nb;
	i = 0;
	while (i < nb)
	{
		if ((PARAM_CBX = (t_checkbox *)malloc(sizeof(t_checkbox))) == NULL)
			error(1);
		PARAM_CBX->align = -1;
		PARAM_CBX->selected = false;
		PARAM_CBX->surface = NULL;
		PARAM_CBX->bmp = NULL;
		PARAM_CBX->nature = CBX;
		i++;
	}
	
}

void	gui_param_checkbox_set_align(t_checkbox *checkbox)
{
	t_gui *gui;

	gui = get_gui();
	if (checkbox->align == GUI_ALIGN_LEFT)
		checkbox->dest.x = PARAM->dest.x;
	else if (checkbox->align == GUI_ALIGN_MID)
		checkbox->dest.x = (GUI_WIDTH / 2) - (checkbox->dest.w / 2);
	else if (checkbox->align == GUI_ALIGN_RIGHT)
		checkbox->dest.x = GUI_WIDTH - checkbox->dest.w;
	else
		checkbox->dest.x = checkbox->align;
}

void	gui_param_checkbox_set(t_gui *gui, char *tag, int align, int y)
{
	int	i;

	i = 0;
	while (i < PARAM->checkbox_qt)
	{
		if (PARAM_CBX->align == -1)
		{
			PARAM_CBX->align = align;
			PARAM_CBX->dest.w = GUI_CHECKBOX_SIZE;
			PARAM_CBX->dest.h = GUI_CHECKBOX_SIZE;
			PARAM_CBX->dest.y = y;
			PARAM_CBX->tag = tag;
			gui_param_checkbox_set_align(PARAM_CBX);
			i = PARAM->checkbox_qt;
		}
		i++;
	}
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
