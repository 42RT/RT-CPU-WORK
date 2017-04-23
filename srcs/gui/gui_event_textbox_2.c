#include <gui.h>

void	event_txb_value_move(t_textbox *textbox)
{
	int	i;

	i = textbox->maxlen;
	while (i > 0)
	{
		textbox->value[i] = textbox->value[i - 1];
		i--;
	}
}

void	event_txb_value_rot(t_textbox *textbox, char nb)
{
	int	i;

	i = textbox->maxlen - 1;
	while (textbox->value[textbox->maxlen - 1] != ' ')
	{
		if (i == textbox->reserved && textbox->value[i] != ' ')
		{
			event_txb_value_clear(textbox, textbox->maxlen);
			i = textbox->maxlen;
		}
		else if (i > textbox->reserved && textbox->value[i - 1] == ' ')
		{
			textbox->value[i - 1] = textbox->value[i];
			textbox->value[i] = ' ';
			i += 2;
		}
		i--;
	}
	if (i != textbox->maxlen - 1)
		i--;
	textbox->value[i] = nb;
}

void	event_txb_backspace(t_textbox *textbox)
{
	int	i;

	i = textbox->maxlen - 1;
	textbox->value[i] = ' ';
	while (i > textbox->reserved)
	{
		textbox->value[i] = textbox->value[i - 1];
		i--;
	}
	textbox->value[textbox->reserved] = ' ';
}

void	event_txb_switch_select(t_gui *gui, t_textbox *textbox)
{
	int	i;

	i = 1;
	if (*(int *)WIDGET == TXB)
	{
		if (textbox->id < BLOCK[textbox->p]->textbox_qt - 1)
			event_txb_select(gui, BLOCK[textbox->p]->textbox[textbox->id + 1]);
		else
		{
			while ((textbox->p + i) < GUI_CONTAINER_TOTAL_NB)
			{
				if (BLOCK[textbox->p + i]->textbox)
				{
					event_txb_select(gui, BLOCK[textbox->p + i]->textbox[0]);
					i = GUI_CONTAINER_TOTAL_NB;
				}
				i++;
				if ((textbox->p + i) == GUI_CONTAINER_TOTAL_NB)
					i = -textbox->p;
			}
		}
	}
}

void	event_txb_value_clear(t_textbox *textbox, int len)
{
	int	i;

	i = 0;
	while (i < len)
		textbox->value[i++] = ' ';
		textbox->value[i] = '\0';
		textbox->vlen = 0;
}
