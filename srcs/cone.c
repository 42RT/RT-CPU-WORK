/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 13:59:20 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 13:56:53 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	create_cone(t_env *env, t_parse data)
{
	t_obj	*obj;

	if ((obj = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		error(1);
	obj->type = 'k';
	obj->vec1 = data.pos;
	obj->vec2 = data.n;
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

t_obj	*test_cone(t_env *env, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	t_vec	x;
	double		det;

	x = calc_vec(POS, ray->pos);
	a = dot(VDIR, VDIR) - (1 + RS * RS) * pow(dot(VDIR, N), 2);
	b = 2 * (dot(VDIR, x) - (1 + RS * RS) * dot(VDIR, N) *
			dot(x, N));
	c = dot(x, x) - (1 + RS * RS) * pow(dot(x, N), 2);
	det = b * b - 4 * a * c;
	if (det > 0)
	{
		if ((D1 = (-b - sqrt(det)) / (2 * a)) > EPS && D1 < RDIST)
			RDIST = D1;
		if ((D2 = (-b + sqrt(det)) / (2 * a)) > EPS && D2 < RDIST)
			RDIST = D2;
		if (RDIST == D1 || RDIST == D2)
			return (env->obj);
	}
	return (NULL);
}

int		test_cone2(t_env *env, t_vec pos, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	t_vec	x;
	double		det;

	x = calc_vec(POS, pos);
	a = dot(ray.vecdir, ray.vecdir) - (1 + RS * RS) *
		pow(dot(ray.vecdir, N), 2);
	b = 2 * (dot(ray.vecdir, x) - (1 + RS * RS) *
			dot(ray.vecdir, N) * dot(x, N));
	c = dot(x, x) - (1 + RS * RS) * pow(dot(x, N), 2);
	det = b * b - 4 * a * c;
	if (det >= 0)
	{
		if ((D1 = (-b - sqrt(det)) / (2 * a)) > EPS && D1 < ray.dist)
			return (1);
		if ((D2 = (-b + sqrt(det)) / (2 * a)) > EPS && D1 < ray.dist)
			return (1);
	}
	return (0);
}
