/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:33:07 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 14:28:20 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec	get_vector(t_env *env)
{
	t_vec	v;
	int			i;

	i = 0;
	while (LINE[i])
	{
		if (ft_isdigit(LINE[i]) || LINE[i] == '-')
		{
			v.x = ft_atod(LINE + i);
			i = gotonextvalue(env, i);
			v.y = ft_atod(LINE + i);
			i = gotonextvalue(env, i);
			v.z = ft_atod(LINE + i);
			while (LINE[i] && LINE[i] != ')')
				++i;
		}
		++i;
	}
	return (v);
}

t_color		get_color_t(t_env *env)
{
	t_color		c;
	int			i;

	i = 0;
	while (LINE[i])
	{
		if (ft_isdigit(LINE[i]) || LINE[i] == '-')
		{
			c.r = ft_atod(LINE + i);
			i = gotonextvalue(env, i);
			c.g = ft_atod(LINE + i);
			i = gotonextvalue(env, i);
			c.b = ft_atod(LINE + i);
			while (LINE[i] && LINE[i] != ')')
				++i;
		}
		++i;
	}
	color_correc_obj(c);
	return (c);
}

t_color		get_color_spot(t_env *env)
{
	t_color		c;
	int			i;

	i = 0;
	while (LINE[i])
	{
		if (ft_isdigit(LINE[i]) || LINE[i] == '-')
		{
			c.r = ft_atod(LINE + i);
			i = gotonextvalue(env, i);
			c.g = ft_atod(LINE + i);
			i = gotonextvalue(env, i);
			c.b = ft_atod(LINE + i);
			while (LINE[i] && LINE[i] != ')')
				++i;
		}
		++i;
	}
	color_correc_spot(c);
	return (c);
}

void		free_file(t_env *env)
{
	t_line	*file;

	file = env->file->next;
	if (env->file->line)
		free(env->file->line);
	if (env->file)
		free(env->file);
	env->file = file;
}

void		old_parse_file(t_env *env)
{
	env->i = 0;
	while (env->file)
	{
		if (!ft_strcmp(LINE, "camera"))
			old_parse_camera(env);
		else if (!ft_strcmp(LINE, "sphere"))
			old_parse_sphere(env);
		else if (!ft_strcmp(LINE, "spot"))
			old_parse_spot(env);
		else if (!ft_strcmp(LINE, "plane"))
			old_parse_plane(env);
		else if (!ft_strcmp(LINE, "cylinder"))
			old_parse_cylinder(env);
		else if (!ft_strcmp(LINE, "cone"))
			old_parse_cone(env);
		else if (LINE[0] == '\0')
			++env->i;
		else
			error(5);
		if (env->file)
			free_file(env);
	}
}
