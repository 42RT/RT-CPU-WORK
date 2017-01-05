/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:05:46 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/11 15:28:49 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	translation(t_vector vec, t_vector trans)
{
	t_vector	vectrans;

	vectrans.x = vec.x + trans.x;
	vectrans.y = vec.y + trans.y;
	vectrans.z = vec.z + trans.z;
	return (vectrans);
}
