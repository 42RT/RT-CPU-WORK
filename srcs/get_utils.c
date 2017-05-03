/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/16 18:51:34 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 23:03:57 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

t_env			*get_env(void)
{
	static t_env	e;

	return (&e);
}

void			*get_func(unsigned int i, int negative)
{
	if (i == SPHERE && negative == 0)
		return (&trace_sphere);
	else if (i == PLANE && negative == 0)
		return (&trace_floor);
	else if (i == DPLANE)
		return (&trace_dfloor);
	else if ((i == CYLINDER || i == GLASS) && negative == 0)
		return (&trace_cylinder);
	else if (i == CONE)
		return (&trace_cone);
	else if (i == DISK)
		return (&trace_disk);
	else if (i == SQUARE)
		return (&trace_square);
	else if (i == PLANE && negative == 1)
		return (&neg_floor);
	else if (i == SPHERE && negative == 1)
		return (&neg_sphere);
	else if (i == CYLINDER && negative == 1)
		return (&neg_cylinder);
	else if (i == CUBE)
		return (&trace_cube);
	else if (i == PARABOLOID)
		return (&trace_paraboloid);
	else
		return (0);
}

void			*get_normale(unsigned int i)
{
	if (i == SPHERE)
		return (&sphere_normale);
	else if (i == PLANE)
		return (&plane_normale);
	else if (i == DPLANE)
		return (&dplane_normale);
	else if (i == CYLINDER || i == GLASS)
		return (&cylinder_normale);
	else if (i == CONE)
		return (&cone_normale);
	else if (i == DISK)
		return (&plane_normale);
	else if (i == SQUARE)
		return (&plane_normale);
	else if (i == CUBE)
		return (&cube_normale);
	else if (i == PARABOLOID)
		return (&paraboloid_normale);
	else
		return (0);
}
