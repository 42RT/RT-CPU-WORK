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

void	gui_textbox_set(int id, char *tag, int align_v, int align_h)
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
			TEXTBOX[i]->tag = tag;
			TEXTBOX[i]->selected = 0;
			TEXTBOX[i]->value = 10;
			TEXTBOX[i]->dest.y = BLOCK[id]->up_lim + align_h;
			i = BLOCK[id]->textbox_qt;
		}
		i++;
	}
}

void	gui_textbox_get_bmp(t_gui *gui, t_textbox *textbox)
{
	if (gui->textbox_selected == textbox)
		textbox->surface = SDL_LoadBMP(GUI_TEXTURE_PATH"textbox_black.bmp");
	else
		textbox->surface = SDL_LoadBMP(GUI_TEXTURE_PATH"textbox_white.bmp");
	if (!textbox->surface)
		gui_error(2);
	textbox->bmp = SDL_CreateTextureFromSurface(gui->img,
		textbox->surface);
	if (!textbox->bmp)
		gui_error(3);
}


void	gui_textbox_display(t_gui *gui, t_textbox *textbox)
{
	if (textbox->align == GUI_ALIGN_LEFT)
		textbox->dest.x = 50;
	else if (textbox->align == GUI_ALIGN_MID)
		textbox->dest.x = (GUI_WIDTH / 2) - (textbox->dest.w / 2) + 10;
	else if (textbox->align == GUI_ALIGN_RIGHT)
		textbox->dest.x = GUI_WIDTH - (textbox->dest.w + 20);
	else
		textbox->dest.x = textbox->align;
	SDL_RenderCopy(gui->img, textbox->bmp, NULL, &textbox->dest);
	SDL_DestroyTexture(textbox->bmp);
	SDL_FreeSurface(textbox->surface);
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
				gui_textbox_get_bmp(gui, TEXTBOX[i]);
				gui_textbox_display(gui, TEXTBOX[i]);
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
