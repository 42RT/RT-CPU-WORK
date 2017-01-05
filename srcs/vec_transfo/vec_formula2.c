/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_formula2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 14:29:45 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/16 16:03:55 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		dotproduct(t_vector vec1, t_vector vec2)
{
	double	res;

	res = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (res);
}

t_vector	reflect_vect(t_vector dir, t_vector n)
{
	t_vector	reflect;

	reflect.x = dir.x - 2 * dotproduct(dir, n) * n.x;
	reflect.y = dir.y - 2 * dotproduct(dir, n) * n.y;
	reflect.z = dir.z - 2 * dotproduct(dir, n) * n.z;
	return (reflect);
}

t_vector	mult_vect(t_vector v, double mult)
{
	t_vector	w;

	w.x = v.x * mult;
	w.y = v.y * mult;
	w.z = v.z * mult;
	return (w);
}

t_vector	sub_vect(t_vector v, t_vector w)
{
	t_vector	z;

	z.x = v.x - w.x;
	z.y = v.y - w.y;
	z.z = v.z - w.z;
	return (z);
}

t_vector	inv_vect(t_vector vec)
{
	vec.x = -vec.x;
	vec.y = -vec.y;
	vec.z = -vec.z;
	return (vec);
}
