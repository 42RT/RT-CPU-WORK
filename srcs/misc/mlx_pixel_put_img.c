/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:59:45 by rfriscca          #+#    #+#             */
/*   Updated: 2016/09/28 15:40:55 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	mlx_pixel_put_img(t_env *env, t_color color)
{
	int		goto_pixel;

	goto_pixel = env->x * env->size_line + env->y * 4;
	env->img_data[goto_pixel] = (char)color.b;
	env->img_data[goto_pixel + 1] = (char)color.g;
	env->img_data[goto_pixel + 2] = (char)color.r;
	env->img_data[goto_pixel + 3] = 0;
}
