/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 13:57:47 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/16 15:16:23 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	create_cylinder(t_env *env, t_parse data)
{
	t_obj	*obj;

	if ((obj = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		error(1);
	obj->type = 'c';
	obj->vec1 = data.pos;
	obj->vec2 = inv_vect(data.n);
	obj->r = data.r;
	obj->reflect = 0;
	obj->d1 = 0;
	obj->d2 = 0;
	obj->color = data.color;
	obj->next = NULL;
	if (env->obj == NULL)
	{
		obj->first = obj;
		env->obj = obj;
	}
	else
	{
		obj->first = env->obj->first;
		while (env->obj->next != NULL)
			env->obj = env->obj->next;
		env->obj->next = obj;
	}
	env->obj = env->obj->first;
}

t_obj	*test_cylinder(t_env *env, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	t_vector	x;
	double		det;

	x = calc_vect(POS, ray->pos);
	a = dotproduct(VDIR, VDIR) - pow(dotproduct(VDIR, N), 2);
	b = 2 * (dotproduct(VDIR, x) - dotproduct(VDIR, N) *
			dotproduct(x, N));
	c = dotproduct(x, x) - pow(dotproduct(x, N), 2) - RS * RS;
	det = b * b - 4 * a * c;
	if (det >= 0)
	{
		if ((D1 = (-b + sqrt(det)) / (2 * a)) > EPS && D1 < RDIST)
			RDIST = D1;
		if ((D2 = (-b - sqrt(det)) / (2 * a)) > EPS && D2 < RDIST)
			RDIST = D2;
		if (RDIST == D1 || RDIST == D2)
			return (env->obj);
	}
	return (NULL);
}

int		test_cylinder2(t_env *env, t_vector pos, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	t_vector	x;
	double		det;

	x = calc_vect(POS, pos);
	a = dotproduct(ray.vecdir, ray.vecdir) - pow(dotproduct(ray.vecdir, N), 2);
	b = 2 * (dotproduct(ray.vecdir, x) - dotproduct(ray.vecdir, N) *
			dotproduct(x, N));
	c = dotproduct(x, x) - pow(dotproduct(x, N), 2) - RS * RS;
	det = b * b - 4 * a * c;
	if (det >= 0)
	{
		if ((D1 = (-b - sqrt(det)) / (2 * a)) > EPS && D1 < ray.dist)
			return (1);
		if ((D2 = (-b + sqrt(det)) / (2 * a)) > EPS && D2 < ray.dist)
			return (1);
	}
	return (0);
}
