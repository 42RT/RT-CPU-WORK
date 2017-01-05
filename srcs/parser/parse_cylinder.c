/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:38:33 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/21 15:21:53 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_cylinder(t_env *env)
{
	t_line		*file;

	env->data.pos = default_pos();
	env->data.color = default_color();
	env->data.n = default_n();
	env->data.r = 1;
	while (env->file->next && (LINENEXT[0] == 'r' || LINENEXT[0] == 't'
				|| LINENEXT[0] == 'o' || LINENEXT[0] == 'c') &&
			!ft_isalpha(LINENEXT[1]))
	{
		file = env->file->next;
		free_file(env);
		env->file = file;
		if (LINE[0] == 't' || LINE[0] == 'r')
			trans_rotation(env);
		else if (LINE[0] == 'c')
			env->data.color = get_color(env);
		else if (LINE[0] == 'o')
			env->data.r = ft_atof(LINE);
	}
	create_cylinder(env, env->data);
}
