/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotz.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:20:13 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 12:22:30 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libvec.h>

t_vec	rotz(t_vec vec, float angle)
{
	t_vec	vecrot;

	vecrot.x = vec.x * cos(angle) - vec.y * sin(angle);
	vecrot.y = vec.x * sin(angle) + vec.y * cos(angle);
	vecrot.z = vec.z;
	return (vecrot);
}
