#include <gui.h>

void	gui_reset(t_gui *gui, char *target)
{
	gui_reparse_scroll_value(gui, target);
	gui_reparse_textbox_value(gui, target);
	gui_reset_gauge_value(gui, target);
}

