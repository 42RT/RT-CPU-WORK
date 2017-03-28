#include <gui.h>

t_textbox	*gui_param_textbox_init(void)
{
	t_textbox *textbox;

	if (!(textbox = (t_textbox *)malloc(sizeof(t_textbox))))
		error(1);
	if (!(textbox->value = (char *)malloc(sizeof(char) * 7)))
		error(1);
	if (!(textbox->tag = (char *)malloc(sizeof(char) * 3)))
		error(1);
	textbox->edited = 0;
	textbox->surface = NULL;
	textbox->bmp = NULL;
	textbox->nature = TXB;
}
