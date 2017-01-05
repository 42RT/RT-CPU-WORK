/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_formula.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 14:06:46 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/15 15:26:09 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	calc_vect(t_vector p1, t_vector p2)
{
	t_vector	new;

	new.x = p2.x - p1.x;
	new.y = p2.y - p1.y;
	new.z = p2.z - p1.z;
	return (new);
}

t_vector	calc_ncylinder(t_ray *ray, t_obj *obj)
{
	t_vector	n;
	double		m;
	t_vector	x;

	x = calc_vect(obj->vec1, ray->pos);
	m = dotproduct(VDIR, obj->vec2) * RDIST + dotproduct(x, obj->vec2);
	n.x = (VDIR.x * RDIST + ray->pos.x) - obj->vec1.x - obj->vec2.x * m;
	n.y = (VDIR.y * RDIST + ray->pos.y) - obj->vec1.y - obj->vec2.y * m;
	n.z = (VDIR.z * RDIST + ray->pos.z) - obj->vec1.z - obj->vec2.z * m;
	return (n);
}

t_vector	calc_ncone(t_ray *ray, t_obj *obj)
{
	t_vector	n;
	double		m;
	t_vector	x;

	x = calc_vect(obj->vec1, ray->pos);
	m = dotproduct(VDIR, obj->vec2) * RDIST + dotproduct(x, obj->vec2);
	n.x = (VDIR.x * RDIST + ray->pos.x) - obj->vec1.x -
		(1 + obj->r * obj->r) * obj->vec2.x * m;
	n.y = (VDIR.y * RDIST + ray->pos.y) - obj->vec1.y -
		(1 + obj->r * obj->r) * obj->vec2.y * m;
	n.z = (VDIR.z * RDIST + ray->pos.z) - obj->vec1.z -
		(1 + obj->r * obj->r) * obj->vec2.z * m;
	return (n);
}

t_vector	normalize_vec(t_vector vec)
{
	t_vector	vecnorm;

	vecnorm.x = vec.x / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vecnorm.y = vec.y / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vecnorm.z = vec.z / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (vecnorm);
}
