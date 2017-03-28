#include <gui.h>

t_gauge		*gui_gauge_init(void)
{
	t_gauge *gauge;

	if (!(gauge = (t_gauge *)malloc(sizeof(t_gauge))))
		error(1);
	if (!(gauge->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
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
		gauge->dest.x = GUI_WIDTH - (gauge->dest.w + 20);
	else
		gauge->dest.x = gauge->dest.x;
}

void		gui_gauge_set(t_gauge *gauge)
{
	//t_gui *gui;

	//gui = get_gui();
	gauge->dest.w = 100;
	gauge->dest.h = 20;
	gui_gauge_set_halign(gauge);
}
