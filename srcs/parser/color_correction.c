/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_correction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 12:57:03 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/12 13:02:27 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		color_correc_obj(t_color color)
{
	if (color.r > 1)
		color.r = 1;
	else if (color.r < 0)
		color.r = 0;
	if (color.g > 1)
		color.g = 1;
	else if (color.g < 0)
		color.g = 0;
	if (color.b > 1)
		color.b = 1;
	else if (color.b < 0)
		color.b = 0;
	return (color);
}

t_color		color_correc_spot(t_color color)
{
	if (color.r > 255)
		color.r = 255;
	else if (color.r < 0)
		color.r = 0;
	if (color.g > 255)
		color.g = 255;
	else if (color.g < 0)
		color.g = 0;
	if (color.b > 255)
		color.b = 255;
	else if (color.b < 0)
		color.b = 0;
	return (color);
}
