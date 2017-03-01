/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 20:34:57 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/09 16:52:51 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <raytracer.h>
#include <gui.h>

void		print_debug(t_env *e)
{
	t_obj	*obj;
	t_light	*light;

	aff_settings(e->set);
	obj = e->obj;
	while (obj)
	{
		aff_obj(obj);
		obj = obj->next;
	}
	light = e->light;
	while (light)
	{
		aff_light(light);
		light = light->next;
	}
}

int			main(int ac, char **av)
{
	t_env		*e;
	t_gui		*gui;

	e = get_env();
	generate_noise(e);
	e->inside_obj = 0;
	e->last_refract = 1;
	e->ac = ac;
	e->av = av;
	init(e, ac, av);
	e->gfx = libxmlx_init(e->set->name, e->set->width,
							e->set->height, BUFF_NB);
	if (!e->gfx)
		return (0);
	//gui = gui_init();
	e->load_bar = create_new_load_bar(e->gfx);
	if (!e->load_bar)
		return (0);
	if (e->set->verbose)
		print_debug(e);
	libxmlx_blitz_black_image(e->gfx, 0, 0);
	if (e->set->preview)
		ft_aff_quick(e, e->obj);
	ft_aff(e, e->obj);
	//libxmlx_exit(e->gfx, 0);
	while(1);
	gui = gui_init();
	while (1)
		wait_event(e);
	(void)gui;
	return (0);
}
