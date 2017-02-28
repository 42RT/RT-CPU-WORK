/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:30:11 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 12:31:30 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libvec.h>

t_vec	calc_vec(t_vec p1, t_vec p2)
{
	t_vec	newvec;

	newvec.x = p2.x - p1.x;
	newvec.y = p2.y - p1.y;
	newvec.z = p2.z - p1.z;
	return (newvec);
}
