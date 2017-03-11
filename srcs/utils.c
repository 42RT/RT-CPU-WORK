/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 23:03:33 by jrouilly          #+#    #+#             */
/*   Updated: 2014/03/27 23:03:33 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <raytracer.h>

int				**new_base(void)
{
	int		**res;

	res = (int **)malloc(3 * sizeof(int *));
	res[0] = (int *)malloc(3 * sizeof(int));
	res[1] = (int *)malloc(3 * sizeof(int));
	res[2] = (int *)malloc(3 * sizeof(int));
	res[0][0] = 1;
	res[0][1] = 0;
	res[0][2] = 0;
	res[1][0] = 0;
	res[1][1] = 1;
	res[1][2] = 0;
	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = 1;
	return (res);
}

t_vector		*reflect_vector(t_obj *obj, t_vector *o, t_vector *v,
								t_vector *n)
{
	float		scal;

	exp_compute(o, &(obj->exp));
	exp_compute(v, &(obj->exp));
	scal = vec_dot(v, n);
	v->x -= 2 * n->x * scal;
	v->y -= 2 * n->y * scal;
	v->z -= 2 * n->z * scal;
	return (v);
}

t_color			new_ray(t_env *e, t_vector *o, t_vector *v, t_obj *obj,
						unsigned int deph)
{
	t_obj		*start;
	t_vector	*vec[2];

	start = obj;
	while (obj)
	{
		trace_ray(e, obj, o, v);
		obj = obj->next;
	}
	vec[0] = o;
	vec[1] = v;
	return (ray_effect(e, vec, start, deph));
}

void			compute_vector(t_env *e, t_vector *v)
{
	float	k;
	float	ang;

	ang = (M_PI * (float)e->set->fov) / 180;
	v->x = e->x - (e->set->width / 2);
	v->y = e->y - (e->set->height / 2);
	v->z = -((float)e->set->width / (2 * tan(ang / 2)));
	rotate_vector(v, e->set->cam->ang.x, e->set->cam->ang.y,
					e->set->cam->ang.z);
	k = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= k;
	v->y /= k;
	v->z /= k;
}
