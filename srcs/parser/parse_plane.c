/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:10:18 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/20 14:43:50 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_plane(t_env *env)
{
	t_line		*file;

	env->data.pos = default_pos();
	env->data.color = default_color();
	env->data.n = default_n();
	while (env->file->next && (LINENEXT[0] == 't' || LINENEXT[0] == 'c'
				|| LINENEXT[0] == 'r') && !ft_isalpha(LINENEXT[1]))
	{
		file = env->file->next;
		free_file(env);
		env->file = file;
		if (LINE[0] == 't' || LINE[0] == 'r')
			trans_rotation(env);
		else if (LINE[0] == 'c')
			env->data.color = get_color(env);
	}
	create_plan(env, env->data.pos, env->data.color, env->data.n);
}
