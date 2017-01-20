#include <rt.h>

void	gui_block_textbox_init(t_gui *gui, int id, int nb)
{
	int i;

	if ((TEXTBOX = (t_textbox **)malloc(sizeof(t_textbox *) * nb)) == NULL)
		error(1);
	BLOCK[id]->textbox_qt = nb;
	i = 0;
	while (i < nb)
	{
		if ((TEXTBOX[i] = (t_textbox *)malloc(sizeof(t_textbox))) == NULL)
			error(1);
		TEXTBOX[i]->align = -1;
		TEXTBOX[i]->surface = NULL;
		TEXTBOX[i]->bmp = NULL;
		i++;
	}
}

void	gui_textbox_set(int id, char *target, int align_v, int align_h)
{
	t_gui	*gui;
	int		i;

	gui = get_gui();
	i = 0;
	while (i < BLOCK[id]->textbox_qt)
	{
		if (TEXTBOX[i]->align == -1)
		{
			TEXTBOX[i]->align = align_v;
			TEXTBOX[i]->dest.w = GUI_TEXTBOX_W;
			TEXTBOX[i]->dest.h = GUI_TEXTBOX_H;
			TEXTBOX[i]->target = target;
			TEXTBOX[i]->dest.y = BLOCK[id]->up_lim + align_h;
			i = BLOCK[id]->textbox_qt;
		}
		i++;
	}
}

void	gui_textbox_get_bmp(t_gui *gui, int id, int i)
{
	TEXTBOX[i]->surface = SDL_LoadBMP(GUI_TEXTURE_PATH"textbox_white.bmp");
	if (!TEXTBOX[i]->surface)
		gui_error(2);
	TEXTBOX[i]->bmp = SDL_CreateTextureFromSurface(gui->img,
		TEXTBOX[i]->surface);
	if (!TEXTBOX[i]->bmp)
		gui_error(3);
}


void	gui_textbox_display(t_gui *gui, int id, int i)
{
	if (TEXTBOX[i]->align == GUI_ALIGN_LEFT)
		TEXTBOX[i]->dest.x = 50;
	else if (TEXTBOX[i]->align == GUI_ALIGN_MID)
		TEXTBOX[i]->dest.x = (GUI_WIDTH / 2) - (TEXTBOX[i]->dest.w / 2) + 10;
	else if (TEXTBOX[i]->align == GUI_ALIGN_RIGHT)
		TEXTBOX[i]->dest.x = GUI_WIDTH - (TEXTBOX[i]->dest.w + 20);
	else
		TEXTBOX[i]->dest.x = TEXTBOX[i]->align;
	SDL_RenderCopy(gui->img, TEXTBOX[i]->bmp, NULL, &TEXTBOX[i]->dest);
	SDL_DestroyTexture(TEXTBOX[i]->bmp);
	SDL_FreeSurface(TEXTBOX[i]->surface);
}

void	gui_textbox_create_all(t_gui *gui)
{
	int i;
	int id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->textbox == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->textbox_qt)
			{
				gui_textbox_get_bmp(gui, id, i);
				gui_textbox_display(gui, id ,i);
				i++;
			}
			id++;
		}
	}
}

void	gui_textbox_build(t_gui *gui)
{
	gui_block_textbox_init(gui, 1, 3);
	gui_block_textbox_init(gui, 2, 2);
	gui_block_textbox_init(gui, 3, 4);
	gui_block_textbox_init(gui, 4, 1);
	gui_block_textbox_init(gui, 5, 1);
	gui_textbox_set(1, "X", GUI_ALIGN_LEFT, 45);
	gui_textbox_set(1, "Y", GUI_ALIGN_MID, 45);
	gui_textbox_set(1, "Z", GUI_ALIGN_RIGHT, 45);
	gui_textbox_set(2, "V", GUI_ALIGN_LEFT, 45);
	gui_textbox_set(2, "H", GUI_ALIGN_MID, 45);
	gui_textbox_set(3, "R", GUI_ALIGN_LEFT, 45);
	gui_textbox_set(3, "G", GUI_ALIGN_MID, 45);
	gui_textbox_set(3, "B", GUI_ALIGN_LEFT, 80);
	gui_textbox_set(3, "A", GUI_ALIGN_MID, 80);
	gui_textbox_set(4, "RFR", GUI_ALIGN_MID, 10);
	gui_textbox_set(5, "RFL", GUI_ALIGN_MID, 10);
	gui_textbox_create_all(gui);
}
