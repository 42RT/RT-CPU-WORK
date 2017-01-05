/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 12:50:46 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/20 14:44:36 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_spot(t_env *env)
{
	t_vector	pos;
	t_vector	trans;
	t_color		color;
	t_line		*file;

	color = default_color_spot();
	pos = default_pos();
	while (env->file->next && (LINENEXT[0] == 't' || LINENEXT[0] == 'c')
			&& !ft_isalpha(LINENEXT[1]))
	{
		file = env->file->next;
		free_file(env);
		env->file = file;
		if (LINE[0] == 't')
		{
			trans = get_vector(env);
			pos = translation(pos, trans);
		}
		else if (LINE[0] == 'c')
			color = get_color_spot(env);
	}
	create_spot(env, pos, color);
}
