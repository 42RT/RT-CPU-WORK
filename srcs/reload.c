/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 03:33:32 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/16 03:33:37 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <parser.h>
#include <stdlib.h>

void		delete_all_obj(t_env *e)
{
	t_obj	*act;
	t_obj	*next;

	act = e->obj;
	while (act)
	{
		next = act->next;
		free(act);
		act = next;
	}
	e->obj = 0;
}

void		reload(t_env *e)
{
	int				i;

	i = 0;
	delete_all_obj(e);
	while (++i < e->ac)
		parse(e, e->av[i]);
	if (e->set->verbose)
		print_debug(e);
	if (!libxmlx_reload(e->gfx, e->set->width, e->set->height, BUFF_NB))
		exit (1);
	if (e->set->preview)
		ft_aff_quick(e, e->obj);
	ft_aff(e, e->obj);
}
