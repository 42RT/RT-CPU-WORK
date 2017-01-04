/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 03:32:19 by rdieulan          #+#    #+#             */
/*   Updated: 2016/11/23 03:32:20 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

t_vec	rot(t_vec v, float hor_angle, float vert_angle)
{
	float tmpx;
	float tmpy;
	float tmpz;

	tmpz = v.z;
	tmpx = v.x;
	tmpy = v.y;
	v.y = (v.y * cos(hor_angle)) - (v.z * sin(hor_angle));
	v.z = (tmpy * sin(hor_angle)) + (v.z * cos(hor_angle));
	tmpx = v.x;
	v.x = (v.x * cos(vert_angle)) + (v.z * sin(vert_angle));
	v.z = (tmpx * (-sin(vert_angle))) + (v.z * cos(vert_angle));
	return (v);
}
