/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_textbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:46:12 by rdieulan         ###   ########.fr       */
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
	if (!CMP(tag, "__X") || !CMP(tag, "__Y") || !CMP(tag, "__Z")
	|| !CMP(tag, "CPX") || !CMP(tag, "CPY") || !CMP(tag, "CPZ")
	|| !CMP(tag, "CAX") || !CMP(tag, "CAY") || !CMP(tag, "CAZ"))
		textbox->maxlen = 6;
	if (!CMP(tag, "_AX") || !CMP(tag, "_AY") || !CMP(tag, "_AZ")
	|| !CMP(tag, "SIZ"))
		textbox->maxlen = 4;
	if (!CMP(tag, "__R") || !CMP(tag, "__G") || !CMP(tag, "__B")
	|| !CMP(tag, "__A") || !CMP(tag, "RFL"))
		textbox->maxlen = 3;
	if (!CMP(tag, "RFR"))
		textbox->maxlen = 5;
	gui_free_str(&tag);
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
	textbox->dest.w = textbox->maxlen * (dest.w / 32);
	textbox->dest.h = DEF->txb_h;
	textbox->dest.y += dest.y;
	gui_textbox_set_halign(textbox, dest);
}
