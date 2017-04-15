/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 15:59:32 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/23 15:02:46 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <parser.h>
#include <math.h>

char	*get_value(char *str)
{
	while (*str && *str != ':')
		++str;
	if (*str)
		++str;
	return (str);
}

t_item	*get_next_item(char **str)
{
	char	*file;
	t_item	*item;
	int		i;

	i = 0;
	file = *str;
	item = (t_item *)malloc(sizeof(t_item));
	item->type = ft_strdup_trim(file);
	item->setnb = 0;
	if (!item)
		return (0);
	file = ft_strchr(file, '{');
	file += (*file != 0);
	while (file && *file)
	{
		if (i == 0)
		{
			if (ft_strcchr(file, '{', '}') != NULL)
				i++;
		}
		if (*file == '}' && i == 0)
			break ;
		else if (*file == '}' && i > 0)
			i--;
		add_next_set(item, &file);
	}
	while (*file && (*file == ' ' || *file == '\n' || *file == '\r'
						|| *file == '\t' || *file == '}' || *file == ','))
		++file;
	*str = file;
	return (item);
}

int		init(t_env *e, char *scene)
{
	e->set = new_settings();
	e->obj = 0;
	e->neg_obj = 0;
	parse(e, scene);
	parse(e, "set.rtc");
	e->worker = 0;
	e->worker_stop = 0;
	e->rendering_preview = 0;
	return (0);
}

void	parse_ang(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "\"x\"", 3))
		v->x = ((float)ft_atoi(get_value(str)) * M_PI_2) / 90;
	else if (!ft_strncmp(str, "\"y\"", 3))
		v->y = ((float)ft_atoi(get_value(str)) * M_PI_2) / 90;
	else if (!ft_strncmp(str, "\"z\"", 3))
		v->z = ((float)ft_atoi(get_value(str)) * M_PI_2) / 90;
}

void	parse_pos(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "\"x\"", 3))
		v->x = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"y\"", 3))
		v->y = ft_atof(get_value(str));
	else if (!ft_strncmp(str, "\"z\"", 3))
		v->z = ft_atof(get_value(str));
}
