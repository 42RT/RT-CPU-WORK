/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 23:20:15 by jrouilly          #+#    #+#             */
/*   Updated: 2014/03/27 23:20:17 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <raytracer.h>
#include <bmp.h>

int			move_cam(t_env *e, int keycode)
{
	t_obj		*obj;

	obj = e->obj;
	if (keycode == A_KEY)
		e->set->cam->pos.x -= MOVE_VAL;
	else if (keycode == D_KEY)
		e->set->cam->pos.x += MOVE_VAL;
	else if (keycode == W_KEY)
		e->set->cam->pos.y -= MOVE_VAL;
	else if (keycode == S_KEY)
		e->set->cam->pos.y += MOVE_VAL;
	ft_aff(e, obj);
	return (0);
}

int			turn_cam(t_env *e, int keycode)
{
	t_obj		*obj;

	obj = e->obj;
	if (keycode == LEFT_ARROW)
		e->set->cam->ang.y += TURN_VAL;
	if (keycode == RIGHT_ARROW)
		e->set->cam->ang.y -= TURN_VAL;
	if (keycode == TOP_ARROW)
		e->set->cam->ang.x += TURN_VAL;
	if (keycode == BOT_ARROW)
		e->set->cam->ang.x -= TURN_VAL;
	ft_aff(e, obj);
	return (0);
}

int			mod_3d(t_env *e, int keycode)
{
	t_obj		*obj;

	obj = e->obj;
	if (keycode == LEFT_ARROW)
		e->set->cam->ang.y += 0.042;
	if (keycode == RIGHT_ARROW)
		e->set->cam->ang.y -= 0.042;
	if (keycode == TOP_ARROW)
		e->set->cam->ang.x += 0.042;
	if (keycode == BOT_ARROW)
		e->set->cam->ang.x -= 0.042;
	ft_aff(e, obj);
	return (0);
}

int			key_hook(int keycode, t_env *e)
{
	static char	mode = 0;

	if (keycode == 65307)
		libxmlx_exit(e->gfx, 0);
	if (keycode == 96)
		mode = !mode;
	if (!mode)
		expose_hook(e);
//	if (mode)
//		mode = rt_console(keycode, e);
	else if (keycode == A_KEY || keycode == W_KEY
				|| keycode == S_KEY || keycode == D_KEY)
		move_cam(e, keycode);
	else if (keycode >= LEFT_ARROW && keycode <= TOP_ARROW)
		turn_cam(e, keycode);
	else if (keycode >= MULT_KEY && keycode <= DIV_KEY)
		mod_3d(e, keycode);
	else if (keycode == F5_KEY)
		reload(e);
	else if (keycode >= KEY_1 && keycode <= KEY_4)
		libxmlx_change_screen(e->gfx, keycode + 1 - KEY_1);
	return (0);
}
