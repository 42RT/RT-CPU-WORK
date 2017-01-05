/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:52:19 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/15 14:37:12 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		main_extension(t_env *env, int fd)
{
	env->file = save_file(fd);
	env->obj = NULL;
	env->spot = NULL;
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
	main_extension(env, fd);
	env->mlx = mlx_init();
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->img_data = mlx_get_data_addr(env->img, &env->bits_per_pixel,
			&env->size_line, &env->endian);
	raycaster(env);
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "RTv1");
	mlx_key_hook(env->win, event, env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}
