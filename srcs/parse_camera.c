/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 12:00:24 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 14:13:06 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	parse_camera(t_env *env)
{
	t_vec	trans;
	t_line		*file;

	env->cam = init_cam(0, 0, 0);
	while (env->file->next && (LINENEXT[0] == 't' || LINENEXT[0] == 'r'))
	{
		file = env->file->next;
		free_file(env);
		env->file = file;
		if (LINE[0] == 't' || LINE[0] == 'r')
		{
			trans = get_vector(env);
			if (LINE[0] == 't')
				transcam(env, trans);
			if (LINE[0] == 'r')
				camangle(env, M_PI * trans.x / 180, M_PI * trans.y / 180
						, M_PI * trans.z / 180);
		}
	}
}
