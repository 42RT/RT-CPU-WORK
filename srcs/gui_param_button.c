#include <gui.h>

t_button	*gui_param_button_init(void)
{
	t_button *button;

	if (!(button = (t_button *)malloc(sizeof(t_button))))
		error(1);
	if (!(button->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	button->surface = NULL;
	button->bmp = NULL;
	button->nature = BTN;
	return (button);
}
