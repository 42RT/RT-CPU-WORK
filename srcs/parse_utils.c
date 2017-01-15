/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 15:59:32 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/11 15:59:32 by jrouilly         ###   ########.fr       */
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

	file = *str;
	item = (t_item *)malloc(sizeof(t_item));
	item->type = ft_strdup_trim(file);
	item->setnb = 0;
	if (!item)
		return (0);
	file = ft_strchr(file, '{');
	file += (*file != 0);
	while (file && *file && *file != '}')
		add_next_set(item, &file);
	while (*file && (*file == ' ' || *file == '\n' || *file == '\r'
						|| *file == '\t' || *file == '}'))
		++file;
	*str = file;
	return (item);
}

int		init(t_env *e, int argc, char **argv)
{
	int		i;

	e->set = new_settings();
	e->obj = 0;
	e->neg_obj = 0;
	i = 0;
	parse(e, ".default.rtc");
	parse(e, ".default.rts");
	while (++i < argc)
		parse(e, argv[i]);
	return (0);
}

void	parse_ang(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "ang_x", 5))
		v->x = ((float)atoi(get_value(str)) * M_PI_2) / 90;
	else if (!ft_strncmp(str, "ang_y", 5))
		v->y = ((float)atoi(get_value(str)) * M_PI_2) / 90;
	else if (!ft_strncmp(str, "ang_z", 5))
		v->z = ((float)atoi(get_value(str)) * M_PI_2) / 90;
}

void	parse_pos(t_vector *v, char *str)
{
	if (!ft_strncmp(str, "pos_x", 5))
		v->x = atof(get_value(str));
	else if (!ft_strncmp(str, "pos_y", 5))
		v->y = atof(get_value(str));
	else if (!ft_strncmp(str, "pos_z", 5))
		v->z = atof(get_value(str));
}
