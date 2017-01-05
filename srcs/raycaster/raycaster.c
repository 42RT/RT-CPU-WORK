/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 14:22:46 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/16 16:16:34 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	init_color_black(void)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	return (color);
}

t_ray	init_ray(t_env *env)
{
	t_ray	ray;
	double	x;
	double	y;
	double	z;

	x = VPUL.x + env->VDYX * env->y * YINDENT -
		env->VDXX * env->x * XINDENT - CAMPOSX;
	y = VPUL.y + env->VDYY * env->y * YINDENT -
		env->VDXY * env->x * XINDENT - CAMPOSY;
	z = VPUL.z + env->VDYZ * env->y * YINDENT -
		env->VDXZ * env->x * XINDENT - CAMPOSZ;
	ray.pos = CAMPOS;
	ray.vecdir.x = x / sqrt(x * x + y * y + z * z);
	ray.vecdir.y = y / sqrt(x * x + y * y + z * z);
	ray.vecdir.z = z / sqrt(x * x + y * y + z * z);
	ray.dist = 1000000;
	ray.color = init_color_black();
	return (ray);
}

void	raycaster(t_env *env)
{
	t_ray	*ray;
	t_color	color;

	ray = (t_ray*)malloc(sizeof(t_ray));
	color = init_color_black();
	env->y = 0;
	env->x = 0;
	while (env->x < HEIGHT)
	{
		while (env->y < WIDTH)
		{
			*ray = init_ray(env);
			color = trace(env, ray, 0);
			mlx_pixel_put_img(env, color);
			++env->y;
		}
		env->y = 0;
		++env->x;
	}
	free(ray);
}
