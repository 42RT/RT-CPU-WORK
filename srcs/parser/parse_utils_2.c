/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 15:59:32 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/11 12:19:18 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <parser.h>

void	parse_error(void)
{
	ft_putstr("Not a valid file\n");
	exit(EXIT_SUCCESS);
}

char	*ft_newstrcat_free(char *dest, char *src)
{
	char	*res;

	res = ft_newstrcat(dest, src);
	free(src);
	return (res);
}

void	parse_rgb(t_color *c, char *str)
{
	if (!ft_strncmp(str, "\"r\"", 3))
		c->r = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"g\"", 3))
		c->g = ft_atoi(get_value(str));
	else if (!ft_strncmp(str, "\"b\"", 3))
		c->b = ft_atoi(get_value(str));
	else
	{
		ft_printf("Bad name in RGB\n");
		exit(EXIT_SUCCESS);
	}
}

char	*pass_s(char *s, char c)
{
	s += ft_strlen_trim2(s);
	s += (*s && *s == c);
	while (*s && (*s == ' ' || *s == '\n' || *s == '\r' || *s == '\t'))
		++s;
	return (s);
}

int		add_next_set(t_item *item, char **file)
{
	char	*buff[2];
	char	*s;

	if (item->setnb >= MAX_PARAM)
		return (0);
	s = *file;
	while (*s && (*s == ' ' || *s == '\n' || *s == '\r' || *s == '\t'))
		++s;
	if (!s)
		return (0);
	buff[0] = ft_strndup(s, ft_strlen_trim2(s));
	s = pass_s(s, ':');
	if (ft_strncmp(buff[0], "},", 2))
	{
		if (!s)
			return (0);
		buff[1] = ft_strndup(s, ft_strlen_trim2(s));
		s = pass_s(s, ',');
		item->set[item->setnb++] = ft_newstrcat_free(buff[0], buff[1]);
	}
	free(buff[0]);
	*file = s;
	return (1);
}
