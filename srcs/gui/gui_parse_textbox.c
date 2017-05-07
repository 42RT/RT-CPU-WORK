/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parse_textbox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 11:36:23 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_get_textbox_value_suite(t_textbox *textbox, t_env *e)
{
	if (!CMP(textbox->tag, "__A"))
		textbox->value = gui_get_textbox_a();
	else if (!CMP(textbox->tag, "SIZ"))
		textbox->value = gui_get_textbox_siz();
	else if (!CMP(textbox->tag, "RFR"))
		textbox->value = gui_get_textbox_rfr();
	else if (!CMP(textbox->tag, "RFL"))
		textbox->value = gui_get_textbox_rfl();
	else if (!CMP(textbox->tag, "CPX"))
		textbox->value = ft_itoa(e->set->cam->pos.x);
	else if (!CMP(textbox->tag, "CPY"))
		textbox->value = ft_itoa(e->set->cam->pos.y);
	else if (!CMP(textbox->tag, "CPZ"))
		textbox->value = ft_itoa(e->set->cam->pos.z);
	else if (!CMP(textbox->tag, "CAX"))
		textbox->value = ft_itoa(e->set->cam->ang.x);
	else if (!CMP(textbox->tag, "CAY"))
		textbox->value = ft_itoa(e->set->cam->ang.y);
	else if (!CMP(textbox->tag, "CAZ"))
		textbox->value = ft_itoa(e->set->cam->ang.z);
	else
		event_txb_value_clear(textbox, textbox->maxlen);
}

void		gui_get_textbox_value(t_textbox *textbox)
{
	t_env	*e;

	e = get_env();
	gui_textbox_get_len(textbox);
	if (!CMP(textbox->tag, "__X"))
		textbox->value = gui_get_textbox_x();
	else if (!CMP(textbox->tag, "__Y"))
		textbox->value = gui_get_textbox_y();
	else if (!CMP(textbox->tag, "__Z"))
		textbox->value = gui_get_textbox_z();
	else if (!CMP(textbox->tag, "_AX"))
		textbox->value = gui_get_textbox_ax();
	else if (!CMP(textbox->tag, "_AY"))
		textbox->value = gui_get_textbox_ay();
	else if (!CMP(textbox->tag, "_AZ"))
		textbox->value = gui_get_textbox_az();
	else if (!CMP(textbox->tag, "__R"))
		textbox->value = gui_get_textbox_r();
	else if (!CMP(textbox->tag, "__G"))
		textbox->value = gui_get_textbox_g();
	else if (!CMP(textbox->tag, "__B"))
		textbox->value = gui_get_textbox_b();
	else
		gui_get_textbox_value_suite(textbox, e);
}
