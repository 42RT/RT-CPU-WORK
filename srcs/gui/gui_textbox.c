/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_textbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

t_textbox	*gui_textbox_init(void)
{
	t_textbox	*textbox;

	if (!(textbox = (t_textbox *)malloc(sizeof(t_textbox))))
		error(1);
	if (!(textbox->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	textbox->surface = NULL;
	textbox->bmp = NULL;
	textbox->nature = TXB;
	textbox->edited = 0;
	return (textbox);
}

void		gui_textbox_get_len(t_textbox *textbox)
{
	char	*tag;

	tag = ft_strdup(textbox->tag);
	if (!ft_strcmp(tag, "__X") || !ft_strcmp(tag, "__Y")
	|| !ft_strcmp(tag, "__Z") || !ft_strcmp(tag, "_CX")
	|| !ft_strcmp(tag, "_CY") || !ft_strcmp(tag, "_CZ"))
		textbox->maxlen = 6;
	if (!ft_strcmp(tag, "_AX") || !ft_strcmp(tag, "_AY")
		|| !ft_strcmp(tag, "_AZ"))
		textbox->maxlen = 4;
	if (!ft_strcmp(tag, "__R") || !ft_strcmp(tag, "__G")
		|| !ft_strcmp(tag, "__B") || !ft_strcmp(tag, "__A")
		|| !ft_strcmp(tag, "RFL"))
		textbox->maxlen = 3;
	if (!ft_strcmp(tag, "RFR"))
		textbox->maxlen = 5;
	free(tag);
}

void		gui_textbox_set_halign(t_textbox *textbox, SDL_Rect dest)
{
	if (textbox->dest.x == GUI_ALIGN_LEFT)
		textbox->dest.x = dest.x + 50;
	else if (textbox->dest.x == GUI_ALIGN_MID)
		textbox->dest.x = ((dest.w + (dest.x * 2.5)) / 2)
		- (textbox->dest.w / 2) + 10;
	else if (textbox->dest.x == GUI_ALIGN_RIGHT)
		textbox->dest.x = (dest.w + (dest.x * 1.5)) - (textbox->dest.w + 20);
	else
		textbox->dest.x = textbox->dest.x;
}

void		gui_textbox_set(t_textbox *textbox, SDL_Rect dest)
{
	t_gui	*gui;

	gui = get_gui();
	textbox->dest.w = textbox->maxlen * (PARAM->dest.w / 32);
	textbox->dest.h = DEF->txb_h;
	if (textbox->p >= 0)
		textbox->dest.y += BLOCK[textbox->p]->dest.y;
	gui_textbox_set_halign(textbox, dest);
}
