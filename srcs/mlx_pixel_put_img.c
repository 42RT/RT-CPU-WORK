/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:59:45 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 13:50:42 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	mlx_pixel_put_img(t_env *env, t_color color)
{
	int		goto_pixel;

	goto_pixel = env->x * env->size_line + env->y * 4;
	env->img_data[goto_pixel] = (char)color.b;
	env->img_data[goto_pixel + 1] = (char)color.g;
	env->img_data[goto_pixel + 2] = (char)color.r;
	env->img_data[goto_pixel + 3] = 0;
}
