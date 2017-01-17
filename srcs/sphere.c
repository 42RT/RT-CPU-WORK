/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 12:17:11 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/17 13:58:46 by rfriscca         ###   ########.fr       */
/*   Updated: 2017/01/12 13:31:59 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	create_sphere(t_env *env, t_vec pos, t_color color, double r)
{
	t_obj	*obj;
	t_vec	pos2;
	float	r2;

	if ((obj = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		error(1);
	obj->type = 's';
	obj->vec1 = pos;
	obj->vec2 = pos;
	obj->r = r;
	obj->reflect = 1;
	obj->textures = "stripes";
	obj->d1 = 0;
	obj->d2 = 0;
	pos2.x = 0;
	pos2.y = 0;
	pos2.z = -0.6;
	r2 = 2.5;
	obj->compose = create_sphere_compose(pos2, color, r2);
	obj->compose->first = obj->compose;
	obj->color_t = color;
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

t_obj	*test_sphere(t_env *env, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	t_vec	x;
	double		det;

	x = calc_vec(POS, ray->pos);
	a = dot(VDIR, VDIR);
	b = 2 * (dot(VDIR, x));
	c = dot(x, x) - RS * RS;
	det = b * b - 4 * a * c;
	if (det >= 0)
	{
		if ((D1 = (-b + sqrt(det)) / (2 * a)) > EPS && D1 < RDIST)
			if (compose_obj(env, ray, D1) == 0)
				RDIST = D1;
		if ((D2 = (-b - sqrt(det)) / (2 * a)) > EPS && D2 < RDIST)
			if (compose_obj(env, ray, D2) == 0)
				RDIST = D2;
		if (RDIST == D1 || RDIST == D2)
			return (env->obj);
	}
	return (NULL);
}

int		test_sphere2(t_env *env, t_vec pos, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	t_vec	x;
	double		det;

	x = calc_vec(POS, pos);
	a = dot(ray.vecdir, ray.vecdir);
	b = 2 * (dot(ray.vecdir, x));
	c = dot(x, x) - RS * RS;
	det = b * b - 4 * a * c;
	if (det >= 0)
	{
		if ((D1 = (-b + sqrt(det)) / (2 * a)) > EPS && D1 < ray.dist)
			if (compose_obj(env, &ray, D1) == 0)
				return (1);
		if ((D2 = (-b - sqrt(det)) / (2 * a)) > EPS && D2 < ray.dist)
			if (compose_obj(env, &ray, D2) == 0)
				return (1);
	}
	return (0);
}
