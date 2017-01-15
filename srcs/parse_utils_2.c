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
#include <libft.h>
#include <parser.h>

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
	if (!s)
		return (0);
	buff[1] = ft_strndup(s, ft_strlen_trim2(s));
	s += ft_strlen_trim2(s);
	s += (*s && *s == ';');
	while (*s && (*s == ' ' || *s == '\n' || *s == '\r' || *s == '\t'))
		++s;
	*file = s;
	item->set[item->setnb++] = ft_newstrcat_free(buff[0], buff[1]);
	return (1);
}
