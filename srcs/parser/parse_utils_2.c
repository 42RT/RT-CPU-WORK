/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 15:59:32 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/05 13:31:49 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <parser.h>

void		parse_error(void)
{
	ft_putstr("Not a valid file\n");
	exit(EXIT_SUCCESS);
}

char		*ft_newstrcat_free(char *dest, char *src)
{
	char	*res;

	res = ft_newstrcat(dest, src);
	free(src);
	return (res);
}

int			add_next_set(t_item *item, char **file)
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
	s += ft_strlen_trim2(s);
	s += (*s && *s == ':');
	while (*s && (*s == ' ' || *s == '\n' || *s == '\r' || *s == '\t'))
		++s;
	if (ft_strncmp(buff[0], "},", 2))
	{
		if (!s)
			return (0);
		buff[1] = ft_strndup(s, ft_strlen_trim2(s));
		s += ft_strlen_trim2(s);
		s += (*s && *s == ',');
		while (*s && (*s == ' ' || *s == '\n' || *s == '\r' || *s == '\t'))
			++s;
		item->set[item->setnb++] = ft_newstrcat_free(buff[0], buff[1]);
		free(buff[0]);
	}
	else
		free(buff[0]);
	*file = s;
	return (1);
}
