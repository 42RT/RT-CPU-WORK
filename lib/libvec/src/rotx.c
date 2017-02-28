/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:15:14 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 12:17:55 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libvec.h>

t_vec	rotx(t_vec vec, float angle)
{
	t_vec	vecrot;

	vecrot.x = vec.x;
	vecrot.y = vec.y * cos(angle) - vec.z * sin(angle);
	vecrot.z = vec.y * sin(angle) + vec.z * cos(angle);
	return (vecrot);
}
