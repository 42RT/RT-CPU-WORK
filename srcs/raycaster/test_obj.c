/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 12:24:29 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/16 14:54:42 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	*test_obj(t_env *env, t_ray *ray)
{
	t_obj	*obj;
	t_obj	*ret;

	obj = NULL;
	ret = NULL;
	while (env->obj->next)
	{
		if (env->obj->type == 's' && (obj = test_sphere(env, ray)) != NULL)
			ret = obj;
		else if (env->obj->type == 'p' && (obj = test_plan(env, ray)) != NULL)
			ret = obj;
		else if (env->obj->type == 'c' &&
				(obj = test_cylinder(env, ray)) != NULL)
			ret = obj;
		else if (env->obj->type == 'k' && (obj = test_cone(env, ray)) != NULL)
			ret = obj;
		env->obj = env->obj->next;
	}
	if (env->obj->type == 's' && (obj = test_sphere(env, ray)) != NULL)
		ret = obj;
	else if (env->obj->type == 'p' && (obj = test_plan(env, ray)) != NULL)
		ret = obj;
	else if (env->obj->type == 'c' &&
			(obj = test_cylinder(env, ray)) != NULL)
		ret = obj;
	else if (env->obj->type == 'k' && (obj = test_cone(env, ray)) != NULL)
		ret = obj;
	env->obj = env->obj->first;
	return (ret);
}
