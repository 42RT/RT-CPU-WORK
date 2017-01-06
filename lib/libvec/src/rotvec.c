/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 12:54:01 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 14:04:37 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib_vec.h"

t_vec	rotvec(t_vec vec, t_vec trans)
{
	vec = rotx(vec, M_PI * trans.x / 180);
	vec = roty(vec, M_PI * trans.y / 180);
	vec = rotz(vec, M_PI * trans.z / 180);
	return (vec);
}
