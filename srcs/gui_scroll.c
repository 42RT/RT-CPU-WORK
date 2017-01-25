#include <rt.h>

void	gui_block_scroll_init(t_gui *gui, int id, int nb)
{
	int i;

	if ((SCROLL = (t_scroll **)malloc(sizeof(t_scroll *) * nb)) == NULL)
		error(1);
	BLOCK[id]->scroll_qt = nb;
	i = 0;
	while (i < nb)
	{
		if ((SCROLL[i] = (t_scroll *)malloc(sizeof(t_scroll))) == NULL)
			error(1);
		if ((SCROLL[i]->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
			error(1);
		SCROLL[i]->align = -1;
		SCROLL[i]->nature = SCL;
		SCROLL[i]->surface = NULL;
		SCROLL[i]->bmp = NULL;
		i++;
	}
}

void	gui_scroll_set(int id, char *tag, int align_v, int align_h)
{
	t_gui	*gui;
	int		i;

	gui = get_gui();
	i = 0;
	while (i < BLOCK[id]->scroll_qt)
	{
		if (SCROLL[i]->align == -1)
		{
			SCROLL[i]->tag = tag;
			SCROLL[i]->align = align_v;
			SCROLL[i]->p = id;
			SCROLL[i]->id = i;
			SCROLL[i]->dest.w = (GUI_WIDTH / 3) - 20;
			SCROLL[i]->dest.h = GUI_SCROLL_H;
			SCROLL[i]->dest.y = BLOCK[id]->up_lim + align_h;
			i = BLOCK[id]->scroll_qt;
		}
		i++;
	}
}

void	gui_scroll_get_bmp(t_gui *gui, t_scroll *scroll)
{
	scroll->surface = SDL_LoadBMP(GUI_TEXTURE_PATH"textbox_white.bmp");
	if (!scroll->surface)
		gui_error(2);
	scroll->bmp = SDL_CreateTextureFromSurface(gui->img, scroll->surface);
	if (!scroll->bmp)
		gui_error(3);
}

void	gui_scroll_display(t_gui *gui, t_scroll *scroll)
{
	if (scroll->align == GUI_ALIGN_LEFT)
		scroll->dest.x = 40;
	else if (scroll->align == GUI_ALIGN_MID)
		scroll->dest.x = (GUI_WIDTH / 2) - (scroll->dest.w / 2) + 10;
	else if (scroll->align == GUI_ALIGN_RIGHT)
		scroll->dest.x = GUI_WIDTH - scroll->dest.w - 50;
	else
		scroll->dest.x = scroll->align;
	SDL_RenderCopy(gui->img, scroll->bmp, NULL, &scroll->dest);
	SDL_DestroyTexture(scroll->bmp);
	SDL_FreeSurface(scroll->surface);
}

void	gui_scroll_create_all(t_gui *gui)
{
	int	i;
	int	id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->scroll == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->scroll_qt)
			{
				gui_scroll_get_bmp(gui, SCROLL[i]);
				gui_scroll_display(gui, SCROLL[i]);
				i++;
			}
			id++;
		}
	}
}

void	gui_scroll_build(t_gui *gui)
{
	gui_block_scroll_init(gui, 0, 2);
	gui_block_scroll_init(gui, 6, 1);
	gui_block_scroll_init(gui, 7, 2);
	gui_scroll_set(0, "SCN", GUI_ALIGN_MID, 15);
	gui_scroll_set(0, "OBJ", GUI_ALIGN_MID, 45);
	gui_scroll_set(6, "MTR", GUI_ALIGN_MID, 15);
	gui_scroll_set(7, "PCD", GUI_ALIGN_LEFT, 45);
	gui_scroll_set(7, "NML", GUI_ALIGN_RIGHT, 45);
	gui_scroll_create_all(gui);
}
