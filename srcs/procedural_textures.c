/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:46:44 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/12 17:08:45 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_color		square(t_vec point)
{
	t_color		color;

	color.r = (1 + sin(point.x * 20)) / 4 + (1 + cos(point.y * 20)) / 4;
	color.g = (1 + sin(point.x * 20)) / 4 + (1 + cos(point.y * 20)) / 4;
	color.b = (1 + sin(point.x * 20)) / 4 + (1 + cos(point.y * 20)) / 4;
	return (color);
}

t_color		stripe(t_vec point)
{
	t_color		color;

	color.r = (1 + sin(point.x * 10)) / 2;
	color.g = (1 + sin(point.x * 10)) / 2;
	color.b = (1 + sin(point.x * 10)) / 2;
	return (color);
}
