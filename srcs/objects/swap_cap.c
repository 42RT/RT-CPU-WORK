/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_cap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 14:20:47 by rfriscca          #+#    #+#             */
/*   Updated: 2017/04/24 14:20:49 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	swap_cap(t_obj *obj)
{
	int		save;

	save = 0;
	if (obj->cap1 > obj->cap2)
	{
		save = obj->cap1;
		obj->cap1 = obj->cap2;
		obj->cap2 = save;
	}
}
