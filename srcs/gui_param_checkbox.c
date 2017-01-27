#include <rt.h>

void	gui_param_checkbox_init(t_gui *gui, int nb)
{
	int i;

	printf("init param checkbox\n");
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

void	gui_param_checkbox_set(t_gui *gui, char *tag, int align, int y)
{
	int	i;

	printf("setting param checkbox\n");
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
			i = PARAM->checkbox_qt;
		}
		i++;
	}
}

void	gui_param_checkbox_create_all(t_gui *gui)
{
	int	i;

	i = 0;
	printf("creating param checkbox\n");
	while (i < PARAM->checkbox_qt)
	{
		if (PARAM_CBX->selected)
		{
			gui_param_checkbox_get_bmp(gui, PARAM_CBX, "checkbox_selected.bmp");
			gui_param_checkbox_display(gui, PARAM_CBX);
			gui_widget_draw_in_line(gui, PARAM_CBX->dest, 3, "teal");
			gui_widget_draw_in_line(gui, PARAM_CBX->dest, 1, "black");
		}
		else
		{
			gui_param_checkbox_get_bmp(gui, PARAM_CBX, "textbox_white.bmp");
			gui_param_checkbox_display(gui, PARAM_CBX);
			gui_widget_draw_in_line(gui, PARAM_CBX->dest, 1, "black");
		}
		i++;
	}
}

void	gui_param_checkbox_get_bmp(t_gui *gui, t_checkbox *checkbox, char *file)
{
	checkbox->surface = SDL_LoadBMP(ft_strjoin(GUI_TEXTURE_PATH, file));
	if (!checkbox->surface)
		gui_error(2);
	checkbox->bmp = SDL_CreateTextureFromSurface(gui->img, checkbox->surface);
	if (!checkbox->bmp)
		gui_error(3);
}

void	gui_param_checkbox_display(t_gui *gui, t_checkbox *checkbox)
{
	if (checkbox->align == GUI_ALIGN_LEFT)
		checkbox->dest.x = PARAM->dest.x;
	else if (checkbox->align == GUI_ALIGN_MID)
		checkbox->dest.x = (GUI_WIDTH / 2) - (checkbox->dest.w / 2);
	else if (checkbox->align == GUI_ALIGN_RIGHT)
		checkbox->dest.x = GUI_WIDTH - checkbox->dest.w;
	else
		checkbox->dest.x = checkbox->align;
	SDL_RenderCopy(gui->img, checkbox->bmp, NULL, &checkbox->dest);
	SDL_DestroyTexture(checkbox->bmp);
	SDL_FreeSurface(checkbox->surface);
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
