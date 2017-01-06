/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			trans_event2(int n, t_env *env)
{
	if (n == 15)
		transcam(env, env->cam.vecdirz);
	else if (n == 3)
		transcam(env, not_vec(env->cam.vecdirz));
	else if (n == 1)
		transcam(env, not_vec(env->cam.vecdirx));
	return (0);
}

int			trans_event(int n, t_env *env)
{
	if (n == 0)
		transcam(env, not_vec(env->cam.vecdiry));
	else if (n == 2)
		transcam(env, env->cam.vecdiry);
	else if (n == 13)
		transcam(env, env->cam.vecdirx);
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
	}
	else if (n == 116)
	{
		rotcam(env, 0, 0, 0.1);
		camangle(env, 0, 0, 0.1);
	}
	else if (n == 121)
	{
		rotcam(env, 0, 0, -0.1);
		camangle(env, 0, 0, -0.1);
	}
	return (0);
}

void		event3(t_env *env)
{
	rotcam(env, 0, 0.1, 0);
	camangle(env, 0, 0.1, 0);
}

int			event(SDL_Event event, t_env *env)
{
	if (event.type == SDL_WINDOWEVENT)
	{
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			SDL_DestroyRenderer(env->img);
			SDL_DestroyWindow(env->win);
			SDL_Quit();
			exit(1);
		}
	}
	/*else if (n == 124)
	{
		rotcam(env, 0.1, 0, 0);
		camangle(env, 0.1, 0, 0);
	}
	else if (n == 123)
	{
		rotcam(env, -0.1, 0, 0);
		camangle(env, -0.1, 0, 0);
	}
	else if (n == 126)
		event3(env);
	else if (n >= 0 && n <= 15)
		trans_event(n, env);
	else
		event2(n, env);*/
	raycaster(env);
	return (0);
}
