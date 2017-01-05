/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/20 14:33:52 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			trans_event2(int n, t_env *env)
{
	if (n == 15)
	{
		transcam(env, env->cam.vecdirz);
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else if (n == 3)
	{
		transcam(env, inv_vect(env->cam.vecdirz));
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else if (n == 1)
	{
		transcam(env, inv_vect(env->cam.vecdirx));
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	return (0);
}

int			trans_event(int n, t_env *env)
{
	if (n == 0)
	{
		transcam(env, inv_vect(env->cam.vecdiry));
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else if (n == 2)
	{
		transcam(env, env->cam.vecdiry);
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else if (n == 13)
	{
		transcam(env, env->cam.vecdirx);
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else
		trans_event2(n, env);
	return (0);
}

int			event2(int n, t_env *env)
{
	if (n == 125)
	{
		rotcam(env, 0, -0.1, 0);
		camangle(env, 0, -0.1, 0);
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else if (n == 116)
	{
		rotcam(env, 0, 0, 0.1);
		camangle(env, 0, 0, 0.1);
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else if (n == 121)
	{
		rotcam(env, 0, 0, -0.1);
		camangle(env, 0, 0, -0.1);
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	return (0);
}

void		event3(t_env *env)
{
	rotcam(env, 0, 0.1, 0);
	camangle(env, 0, 0.1, 0);
	raycaster(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int			event(int n, t_env *env)
{
	if (n == 53)
		exit(1);
	else if (n == 124)
	{
		rotcam(env, 0.1, 0, 0);
		camangle(env, 0.1, 0, 0);
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else if (n == 123)
	{
		rotcam(env, -0.1, 0, 0);
		camangle(env, -0.1, 0, 0);
		raycaster(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	else if (n == 126)
		event3(env);
	else if (n >= 0 && n <= 15)
		trans_event(n, env);
	else
		event2(n, env);
	return (0);
}
