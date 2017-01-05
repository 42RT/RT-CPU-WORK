/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:33:07 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/20 14:55:55 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	get_vector(t_env *env)
{
	t_vector	v;
	int			i;

	i = 0;
	while (LINE[i])
	{
		if (ft_isdigit(LINE[i]) || LINE[i] == '-')
		{
			v.x = ft_atof(LINE + i);
			i = gotonextvalue(env, i);
			v.y = ft_atof(LINE + i);
			i = gotonextvalue(env, i);
			v.z = ft_atof(LINE + i);
			while (LINE[i] && LINE[i] != ')')
				++i;
		}
		++i;
	}
	return (v);
}

t_color		get_color(t_env *env)
{
	t_color		c;
	int			i;

	i = 0;
	while (LINE[i])
	{
		if (ft_isdigit(LINE[i]) || LINE[i] == '-')
		{
			c.r = ft_atof(LINE + i);
			i = gotonextvalue(env, i);
			c.g = ft_atof(LINE + i);
			i = gotonextvalue(env, i);
			c.b = ft_atof(LINE + i);
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
			c.r = ft_atof(LINE + i);
			i = gotonextvalue(env, i);
			c.g = ft_atof(LINE + i);
			i = gotonextvalue(env, i);
			c.b = ft_atof(LINE + i);
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

void		parse_file(t_env *env)
{
	env->i = 0;
	while (env->file)
	{
		if (!ft_strcmp(LINE, "camera"))
			parse_camera(env);
		else if (!ft_strcmp(LINE, "sphere"))
			parse_sphere(env);
		else if (!ft_strcmp(LINE, "spot"))
			parse_spot(env);
		else if (!ft_strcmp(LINE, "plane"))
			parse_plane(env);
		else if (!ft_strcmp(LINE, "cylinder"))
			parse_cylinder(env);
		else if (!ft_strcmp(LINE, "cone"))
			parse_cone(env);
		else if (LINE[0] == '\0')
			++env->i;
		else
			error(5);
		if (env->file)
			free_file(env);
	}
}
