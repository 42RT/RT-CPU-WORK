/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/16 18:51:34 by jrouilly          #+#    #+#             */
/*   Updated: 2014/09/16 18:51:34 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_env			*get_env(void)
{
	static t_env	e;

	return (&e);
}

/*void			*get_func(unsigned int i)
{
	if (i == SPHERE)
		return (&trace_sphere);
	else if (i == PLANE)
		return (&trace_floor);
	else if (i == DPLANE)
		return (&trace_dfloor);
	else if (i == CYLINDER)
		return (&trace_cylinder);
	else if (i == CONE)
		return (&trace_cone);
	else if (i == DISK)
		return (&trace_disk);
	else if (i == SQUARE)
		return (&trace_square);
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
	else if (i == CYLINDER)
		return (&cylinder_normale);
	else if (i == CONE)
		return (&cylinder_normale);
	else if (i == DISK)
		return (&plane_normale);
	else if (i == SQUARE)
		return (&plane_normale);
	else
		return (0);
}*/
