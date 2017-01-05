/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 12:45:49 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/15 14:34:34 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_sphere(t_env *env)
{
	t_vector	trans;
	t_line		*file;

	env->data.color = default_color();
	env->data.pos = default_pos();
	env->data.r = 1;
	while (env->file->next && (LINENEXT[0] == 't' || LINENEXT[0] == 'c'
				|| LINENEXT[0] == 'o') && !ft_isalpha(LINENEXT[1]))
	{
		file = env->file->next;
		free_file(env);
		env->file = file;
		if (LINE[0] == 't')
		{
			trans = get_vector(env);
			env->data.pos = translation(env->data.pos, trans);
		}
		else if (LINE[0] == 'c')
			env->data.color = get_color(env);
		else if (LINE[0] == 'o')
			env->data.r = ft_atof(LINE);
	}
	create_sphere(env, env->data.pos, env->data.color, env->data.r);
}
