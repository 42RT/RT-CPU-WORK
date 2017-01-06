/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 13:57:47 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 13:58:35 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	create_cylinder(t_env *env, t_parse data)
{
	t_obj	*obj;

	if ((obj = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		error(1);
	obj->type = 'c';
	obj->vec1 = data.pos;
	obj->vec2 = not_vec(data.n);
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
	t_vec	x;
	double		det;

	x = calc_vec(POS, ray->pos);
	a = dot(VDIR, VDIR) - pow(dot(VDIR, N), 2);
	b = 2 * (dot(VDIR, x) - dot(VDIR, N) *
			dot(x, N));
	c = dot(x, x) - pow(dot(x, N), 2) - RS * RS;
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

int		test_cylinder2(t_env *env, t_vec pos, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	t_vec	x;
	double		det;

	x = calc_vec(POS, pos);
	a = dot(ray.vecdir, ray.vecdir) - pow(dot(ray.vecdir, N), 2);
	b = 2 * (dot(ray.vecdir, x) - dot(ray.vecdir, N) *
			dot(x, N));
	c = dot(x, x) - pow(dot(x, N), 2) - RS * RS;
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
