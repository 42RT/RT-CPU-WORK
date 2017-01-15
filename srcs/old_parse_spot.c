/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 12:50:46 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 14:06:20 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	old_parse_spot(t_env *env)
{
	t_vec	pos;
	t_vec	trans;
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
			pos = add_vec(pos, trans);
		}
		else if (LINE[0] == 'c')
			color = get_color_spot(env);
	}
	create_spot(env, pos, color);
}
