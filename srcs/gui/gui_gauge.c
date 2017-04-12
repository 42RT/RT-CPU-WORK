#include <gui.h>

void		gui_reset_gauge_value(t_gui *gui, char *target)
{
	int i;
	int	id;

	if (!ft_strcmp(target, "MAIN") || !ft_strcmp(target, "ALL"))
	{
		id = 0;
		while (id < GUI_CONTAINER_TOTAL_NB)
		{
			if (BLOCK[id]->gauge == NULL)
				id++;
			else
			{
				i = 0;
				while (i < BLOCK[id]->gauge_qt)
				{
					GAUGE[i]->active_value = GAUGE[i]->old_active;
					GAUGE[i]->cursor->dest.x = GAUGE[i]->cursor->oldx;
					i++;
				}
				id++;
			}
		}
	}
	else if (!ft_strcmp(target, "PARAM") || !ft_strcmp(target, "ALL"))
	{
		i = 0;
		while (i < PARAM->gauge_qt)
		{
			PARAM_GAU->active_value = PARAM_GAU->old_active;
			PARAM_GAU->cursor->dest.x = PARAM_GAU->cursor->oldx;
			i++;
		}
	}
}

t_button	*gui_gauge_cursor_init()
{
	t_button	*cursor;

	if (!(cursor = (t_button *)malloc(sizeof(t_button))))
		error(1);
	cursor->nature = BTN;
	cursor->action = "gauge";
	cursor->surface = NULL;
	cursor->bmp = NULL;
	return (cursor);
}

t_gauge		*gui_gauge_init(void)
{
	t_gauge *gauge;

	if (!(gauge = (t_gauge *)malloc(sizeof(t_gauge))))
		error(1);
	if (!(gauge->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	gauge->cursor = gui_gauge_cursor_init();
	gauge->surface = NULL;
	gauge->bmp = NULL;
	gauge->nature = GAU;
	return (gauge);
}

void		gui_gauge_set_halign(t_gauge *gauge)
{
	t_gui *gui;

	gui = get_gui();
	if (gauge->dest.x == GUI_ALIGN_LEFT)
		gauge->dest.x = 50;
	else if (gauge->dest.x == GUI_ALIGN_MID)
		gauge->dest.x = (GUI_WIDTH / 2) - (gauge->dest.w / 2) + 10;
	else if (gauge->dest.x == GUI_ALIGN_RIGHT)
		gauge->dest.x = GUI_WIDTH - (gauge->dest.w + 100);
	else
		gauge->dest.x = gauge->dest.x;
}

void		gui_gauge_set(t_gauge *gauge)
{
	t_gui *gui;

	gui = get_gui();
	gauge->dest.w = DEF->gau_w;
	gauge->dest.h = DEF->gau_h;
	gui_gauge_set_halign(gauge);
	gauge->cursor->dest.w = 11;
	gauge->cursor->dest.h = 12;
	gauge->cursor->dest.x = gauge->dest.x;
	gauge->cursor->dest.y = gauge->dest.y - 1;
}

void		gui_gauge_convert_value(t_gauge *gauge)
{
	float	value;

	value = gauge->active_value;
	if (!ft_strcmp(gauge->tag, "DPH"))
		gauge->txt->content = ft_itoa((int)value);
	else if (!ft_strcmp(gauge->tag, "FOV"))
		gauge->txt->content = ft_itoa((int)value);
	else if (!ft_strcmp(gauge->tag, "CON") || !ft_strcmp(gauge->tag, "LUM"))
		gauge->txt->content = ft_ftoa(value, 2);
	else
		gauge->txt->content = ft_itoa((int)value);
}

float	gui_gauge_get_norm(t_gauge *gauge)
{
	float norm;

	if (!ft_strcmp(gauge->tag, "DPH"))
		norm = gauge->active_value / gauge->mod;
	else if (!ft_strcmp(gauge->tag, "FOV"))
		norm = gauge->active_value + gauge->mod;
	else if (!ft_strcmp(gauge->tag, "CON"))
		norm = gauge->active_value / gauge->mod;
	else if (!ft_strcmp(gauge->tag, "LUM"))
		norm = gauge->active_value / gauge->mod;
	else
		norm = gauge->mod / gauge->active_value;
	return (norm);
}

void		gui_gauge_get_value(t_gauge *gauge)
{
	t_env *e;

	e = get_env();
	if (!ft_strcmp(gauge->tag, "DPH"))
	{
		gauge->active_value = e->set->deph;
		gauge->old_active = gauge->active_value;
		gauge->mod = 10;
		gauge->cursor->dest.x += (gauge->active_value * gauge->mod);
		gauge->cursor->oldx = gauge->cursor->dest.x;
	}
	else if (!ft_strcmp(gauge->tag, "FOV"))
	{
		gauge->active_value = e->set->fov;
		gauge->old_active = gauge->active_value;
		gauge->mod = 30;
		gauge->cursor->dest.x += (gauge->active_value - gauge->mod);
		gauge->cursor->oldx = gauge->cursor->dest.x;
	}
	else if (!ft_strcmp(gauge->tag, "CON"))
	{
		gauge->active_value = 0.5;
		gauge->old_active = gauge->active_value;
		gauge->mod = 100;
		gauge->cursor->dest.x += (gauge->active_value * gauge->mod);
		gauge->cursor->oldx = gauge->cursor->dest.x;
	}
	else if (!ft_strcmp(gauge->tag, "LUM"))
	{
		gauge->active_value = 0.5;
		gauge->old_active = gauge->active_value;
		gauge->mod = 100;
		gauge->cursor->dest.x += (gauge->active_value * gauge->mod);
		gauge->cursor->oldx = gauge->cursor->dest.x;
	}
	else
	{
		gauge->active_value = 50;
		gauge->old_active = gauge->active_value;
		gauge->mod = 1;
		gauge->cursor->dest.x += (gauge->active_value * gauge->mod);
		gauge->cursor->oldx = gauge->cursor->dest.x;
	}
}
