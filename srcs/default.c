/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 17:26:41 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 13:50:21 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec	default_n(void)
{
	t_vec	n;

	n.x = 1;
	n.y = 0;
	n.z = 0;
	return (n);
}

t_color		default_color_spot(void)
{
	t_color		color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	return (color);
}

t_color		default_color(void)
{
	t_color		color;

	color.r = 1;
	color.g = 1;
	color.b = 1;
	return (color);
}

t_vec	default_pos(void)
{
	t_vec	v;

	v.x = 0;
	v.y = 0;
	v.z = 0;
	return (v);
}
