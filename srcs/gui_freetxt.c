#include <gui.h>

t_freetxt	*gui_freetxt_init(void)
{
	t_freetxt	*freetxt;

	if (!(freetxt = (t_freetxt *)malloc(sizeof(t_freetxt))))
		error(1);
	if (!(freetxt->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	freetxt->nature = FTT;
	return (freetxt);
}

void	gui_freetxt_set(t_freetxt *freetxt, SDL_Rect dest)
{
	freetxt->dest.w = ft_strlen(freetxt->txt->content) * 10;
	freetxt->dest.h = 20;
	if (freetxt->dest.x == GUI_ALIGN_LEFT)
		freetxt->dest.x = dest.x + 15;
	else if (freetxt->dest.x == GUI_ALIGN_MID)
		freetxt->dest.x = ((dest.w + (dest.x * 2.5)) / 2) - (freetxt->dest.w / 2) + 10;
	else if (freetxt->dest.x == GUI_ALIGN_RIGHT)
		freetxt->dest.x = (dest.w + (dest.x * 1.5)) - (freetxt->dest.w + 20);
	else
		freetxt->dest.x = freetxt->dest.x;
}
