/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roty.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:18:01 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 12:20:05 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

t_vec	roty(t_vec vec, float angle)
{
	t_vec	vecrot;

	vecrot.x = vec.x * cos(angle) + vec.z * sin(angle);
	vecrot.y = vec.y;
	vecrot.z = vec.z * cos(angle) - vec.x * sin(angle);
	return (vecrot);
}
