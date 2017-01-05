/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:11:56 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/13 14:11:56 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	vpupleft(t_camera cam)
{
	t_vector	new;

	new.x = cam.campos.x + VDZX * VPDIST +
		VDXX * VPHEIGHT / 2.0 - VDYX * VPWIDTH / 2.0;
	new.y = cam.campos.y + VDZY * VPDIST +
		VDXY * VPHEIGHT / 2.0 - VDYY * VPWIDTH / 2.0;
	new.z = cam.campos.z + VDZZ * VPDIST +
		VDXZ * VPHEIGHT / 2.0 - VDYZ * VPWIDTH / 2.0;
	return (new);
}

void		camangle(t_env *env, double rx, double ry, double rz)
{
	if (rx != 0)
	{
		env->cam.vecdirx = rotx(env->cam.vecdirx, rx);
		env->cam.vecdiry = rotx(env->cam.vecdiry, rx);
		env->cam.vecdirz = rotx(env->cam.vecdirz, rx);
	}
	if (ry != 0)
	{
		env->cam.vecdirx = roty(env->cam.vecdirx, ry);
		env->cam.vecdiry = roty(env->cam.vecdiry, ry);
		env->cam.vecdirz = roty(env->cam.vecdirz, ry);
	}
	if (rz != 0)
	{
		env->cam.vecdirx = rotz(env->cam.vecdirx, rz);
		env->cam.vecdiry = rotz(env->cam.vecdiry, rz);
		env->cam.vecdirz = rotz(env->cam.vecdirz, rz);
	}
	env->cam.vpul = vpupleft(env->cam);
}

void		rotcam(t_env *env, double rx, double ry, double rz)
{
	if (rx != 0)
		env->cam.campos = rotx(env->cam.campos, rx);
	if (ry != 0)
		env->cam.campos = roty(env->cam.campos, ry);
	if (rz != 0)
		env->cam.campos = rotz(env->cam.campos, rz);
	env->cam.vpul = vpupleft(env->cam);
}

void		transcam(t_env *env, t_vector trans)
{
	CAMPOS = translation(CAMPOS, trans);
	env->cam.vpul = vpupleft(env->cam);
}

t_camera	init_cam(double x, double y, double z)
{
	t_camera	cam;

	cam.campos.x = x;
	cam.campos.y = y;
	cam.campos.z = z;
	cam.vecdirx.x = 1;
	cam.vecdirx.y = 0;
	cam.vecdirx.z = 0;
	cam.vecdiry.x = 0;
	cam.vecdiry.y = 1;
	cam.vecdiry.z = 0;
	cam.vecdirz.x = 0;
	cam.vecdirz.y = 0;
	cam.vecdirz.z = 1;
	cam.vpul = vpupleft(cam);
	cam.xindent = VPHEIGHT / (double)HEIGHT;
	cam.yindent = VPWIDTH / (double)WIDTH;
	return (cam);
}
