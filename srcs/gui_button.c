#include <rt.h>

void	gui_block_button_init(t_gui *gui, int id, int nb)
{
	int i;

	if ((BUTTON = (t_button **)malloc(sizeof(t_button *) * nb)) == NULL)
		error(1);
	BLOCK[id]->button_qt = nb;
	i = 0;
	while (i < nb)
	{
		if ((BUTTON[i] = (t_button *)malloc(sizeof(t_button))) == NULL)
			error(1);
		BUTTON[i]->align = -1;
		BUTTON[i]->surface = NULL;
		BUTTON[i]->bmp = NULL;
		i++;
	}
}

void	gui_button_get_bmp(t_gui *gui, int id, int i)
{
	BUTTON[i]->surface = SDL_LoadBMP(GUI_TEXTURE_PATH"button.bmp");
	if (!BUTTON[i]->surface)
		gui_error(2);
	BUTTON[i]->bmp = SDL_CreateTextureFromSurface(gui->img,
	BUTTON[i]->surface);
	if (!BUTTON[i]->bmp)
		gui_error(3);
}

void	gui_button_display(t_gui *gui, int id, int i)
{
	BUTTON[i]->dest.w = BUTTON[i]->w;
	BUTTON[i]->dest.h = BUTTON[i]->h;
	if (BUTTON[i]->align == GUI_ALIGN_LEFT)
		BUTTON[i]->dest.x = 10;
	else if (BUTTON[i]->align == GUI_ALIGN_MID)
		BUTTON[i]->dest.x = (GUI_WIDTH / 2) - (BUTTON[i]->w / 2);
	else if (BUTTON[i]->align == GUI_ALIGN_RIGHT)
		BUTTON[i]->dest.x = GUI_WIDTH - (BUTTON[i]->w + 10);
	else
		BUTTON[i]->dest.x = BUTTON[i]->align;
	BUTTON[i]->dest.y = BLOCK[id]->up_lim + (BLOCK[id]->px / 4);
	SDL_RenderCopy(gui->img, BUTTON[i]->bmp, NULL, &BUTTON[i]->dest);
	SDL_DestroyTexture(BUTTON[i]->bmp);
	SDL_FreeSurface(BUTTON[i]->surface);
}

void	gui_button_create_all(t_gui *gui)
{
	int i;
	int id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->button == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->button_qt)
			{
				gui_button_get_bmp(gui, id, i);
				gui_button_display(gui, id ,i);
				i++;
			}
			id++;
		}
	}
}

void	gui_button_set(int id, int align, int w, int h)
{
	t_gui	*gui;
	int		i;

	gui = get_gui();
	i = 0;
	while (i < BLOCK[id]->button_qt)
	{
		if (BUTTON[i]->align == -1)
		{
			BUTTON[i]->align = align;
			BUTTON[i]->w = w;
			BUTTON[i]->h = h;
			i = BLOCK[id]->button_qt;
		}
		i++;
	}
}

void	gui_button_build(t_gui *gui)
{
	printf("GUI : \033[33mButton \033[0m: ");
	gui_block_button_init(gui, 4, 3);
	gui_block_button_init(gui, 5, 3);
	gui_button_set(4, GUI_ALIGN_LEFT, (GUI_WIDTH - 40) / 3, BLOCK[4]->px - 20);
	gui_button_set(4, GUI_ALIGN_MID, (GUI_WIDTH - 40) / 3, BLOCK[4]->px - 20);
	gui_button_set(4, GUI_ALIGN_RIGHT, (GUI_WIDTH - 40) / 3, BLOCK[4]->px - 20);
	gui_button_set(5, GUI_ALIGN_LEFT, (GUI_WIDTH - 40) / 3, BLOCK[5]->px - 20);
	gui_button_set(5, GUI_ALIGN_MID, (GUI_WIDTH - 40) / 3, BLOCK[5]->px - 20);
	gui_button_set(5, GUI_ALIGN_RIGHT, (GUI_WIDTH - 40) / 3, BLOCK[5]->px - 20);
	gui_button_create_all(gui);
	printf("\033[1;32mOK\033[0m\n");
}
