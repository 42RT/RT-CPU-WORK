/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:52:19 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 18:01:15 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		init_env(t_env *env, int fd)
{
	env->file = save_file(fd);
	env->obj = NULL;
	env->spot = NULL;
	env->win = NULL;
	parse_file(env);
	if (env->obj == NULL)
		error(6);
	if (env->spot == NULL)
		error(4);
}



int			main(int argc, char **argv)
{
	t_env		*env;
	int			fd;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		error(1);
	if (argc != 2)
		error(2);
	fd = open(argv[1], O_RDONLY);
	init_env(env, fd);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		error(7);
		return (-1);
	}
	env->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (env->win)
	{
		env->img = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_SOFTWARE);
		raycaster(env);
		while (1)
		{
			SDL_WaitEvent(&env->event);
			event(env->event, env);
		}
	}
	else
		error(8);
	return (0);
}
