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
	return (norm);
}

void		gui_gauge_get_value_suite(t_gauge *gauge, t_env *e)
{
	if (!ft_strcmp(gauge->tag, "CON"))
	{
		gauge->active_value = e->set->contrast;
		gauge->mod = 1;
	}
	else if (!ft_strcmp(gauge->tag, "LUM"))
	{
		gauge->active_value = e->set->luminosity;
		gauge->mod = 6;
	}
	else if (!ft_strcmp(gauge->tag, "MLT"))
	{
		gauge->active_value = e->set->threads;
		gauge->mod = 15;
	}
	gauge->old_active = gauge->active_value;
	gauge->cursor->dest.x += (gauge->active_value
		* (gauge->dest.w / gauge->mod) - gauge->min);
	gauge->cursor->oldx = gauge->cursor->dest.x;
}

void		gui_gauge_get_value(t_gauge *gauge)
{
	t_env	*e;

	e = get_env();
	if (!ft_strcmp(gauge->tag, "DPH"))
	{
		gauge->active_value = e->set->deph;
		gauge->mod = 10;
	}
	else if (!ft_strcmp(gauge->tag, "FOV"))
	{
		gauge->active_value = e->set->fov;
		gauge->mod = 100;
	}
	gui_gauge_get_value_suite(gauge, e);
}
