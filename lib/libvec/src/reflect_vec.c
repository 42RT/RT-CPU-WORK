/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_vec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 12:07:29 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 12:16:04 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libvec.h>

t_vec	reflect_vec(t_vec dir, t_vec n)
{
	t_vec	reflect;

	reflect.x = dir.x - 2 * dot(dir, n) * n.x;
	reflect.y = dir.y - 2 * dot(dir, n) * n.y;
	reflect.z = dir.z - 2 * dot(dir, n) * n.z;
	return (reflect);
}
