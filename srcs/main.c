/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:52:19 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/17 14:18:34 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <parser.h>

t_env		*init_env(int fd)
{
	t_env *env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
			error(1);
	env->file = save_file(fd);
	env->obj = NULL;
	env->spot = NULL;
	env->win = NULL;
	env->set = new_settings();
	old_parse_file(env);
	if (env->obj == NULL)
		error(6);
	if (env->spot == NULL)
		error(4);
	return (env);
}

void		init_graphics(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error(7);
	env->win = SDL_CreateWindow(env->set->name, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, env->set->width, env->set->height,
			SDL_WINDOW_SHOWN);
	if (env->win)
		env->img = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	else
		error(8);
}

int			main(int argc, char **argv)
{
	t_env		*env;
	t_gui		*gui;
	int			fd;

	if (argc != 2)
		error(2);
	fd = open(argv[1], O_RDONLY);
	env = init_env(fd);
	parse(env, ".default.rtc");
	init_graphics(env);
	aff_settings(env->set);
	gui = gui_init();
	raycaster(env);
	while (1)
	{
		SDL_WaitEvent(&env->event);
		event(env->event, env);
	}
	(void)gui;
	return (0);
}
