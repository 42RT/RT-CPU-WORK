/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_gauge_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_reset_gauge_value_suite(t_gui *gui, int id, int i)
{
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->gauge == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->gauge_qt)
			{
				GAUGE[i]->active_value = GAUGE[i]->old_active;
				GAUGE[i]->cursor->dest.x = GAUGE[i]->cursor->oldx;
				i++;
			}
			id++;
		}
	}
}

void		gui_reset_gauge_value(t_gui *gui, char *target)
{
	int	i;

	if (!ft_strcmp(target, "PARAM") || !ft_strcmp(target, "ALL"))
	{
		i = 0;
		while (i < PARAM->gauge_qt)
		{
			PARAM_GAU->active_value = PARAM_GAU->old_active;
			PARAM_GAU->cursor->dest.x = PARAM_GAU->cursor->oldx;
			i++;
		}
	}
	else if (!ft_strcmp(target, "MAIN") || !ft_strcmp(target, "ALL"))
		gui_reset_gauge_value_suite(gui, 0, 0);
}

float		gui_gauge_get_norm(t_gauge *gauge)
{
	float	norm;

	norm = gauge->active_value / (gauge->dest.w / gauge->mod) + gauge->min;
	if (!ft_strcmp(gauge->tag, "LUM"))
		norm -= 3;
	return (norm);
}

void		gui_gauge_get_value(t_gauge *gauge)
{
	t_env	*e;

	e = get_env();
	if (!ft_strcmp(gauge->tag, "DPH"))
		gauge->active_value = e->set->deph;
	else if (!ft_strcmp(gauge->tag, "FOV"))
		gauge->active_value = e->set->fov;
	else if (!ft_strcmp(gauge->tag, "CON"))
		gauge->active_value = e->set->contrast;
	else if (!ft_strcmp(gauge->tag, "SAT"))
		gauge->active_value = e->set->saturation;
	else if (!ft_strcmp(gauge->tag, "LUM"))
		gauge->active_value = e->set->luminosity;
	else if (!ft_strcmp(gauge->tag, "MLT"))
		gauge->active_value = e->set->threads;
	gauge->old_active = gauge->active_value;
	gauge->mod = gauge->max - gauge->min;
	if (!ft_strcmp(gauge->tag, "LUM"))
		gauge->cursor->dest.x += ((gauge->active_value + 3)
			* (gauge->dest.w / gauge->mod) - gauge->min);
	else
		gauge->cursor->dest.x += (gauge->active_value
			* (gauge->dest.w / gauge->mod) - gauge->min);
	gauge->cursor->oldx = gauge->cursor->dest.x;
}
