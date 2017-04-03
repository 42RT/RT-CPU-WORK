#include <gui.h>

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
	gauge->cursor->dest.x = gauge->dest.x + (gauge->dest.w / 2) 
	- (gauge->cursor->dest.w / 2);
	gauge->cursor->dest.y = gauge->dest.y - 1;
}

void		gui_gauge_normalize_value(t_gauge *gauge)
{
	float	value;

	value = gauge->cursor->dest.x - (gauge->cursor->dest.w / 2) 
	- gauge->dest.x + 10;
	if (!ft_strcmp(gauge->tag, "DPH"))
	{
		value /= 10;
		gauge->txt->content = ft_itoa((int)value);
	}
	else if (!ft_strcmp(gauge->tag, "FOV"))
	{
		value += 30;
		gauge->txt->content = ft_itoa((int)value);
	}
	else if (!ft_strcmp(gauge->tag, "CON") || !ft_strcmp(gauge->tag, "LUM"))
	{
		value /= 100;
		gauge->txt->content = ft_ftoa(value, 2);
	}
	else
		gauge->txt->content = ft_itoa((int)value);
}
