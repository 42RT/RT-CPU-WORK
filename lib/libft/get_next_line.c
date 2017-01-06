/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 12:28:58 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/07 15:51:17 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_buf	ft_realloc(int const fd, t_buf buf)
{
	if (buf.i == buf.size)
	{
		buf.i = 0;
		if (!buf.buf)
			if ((buf.buf = (char*)malloc(sizeof(*buf.buf) * BUF_SIZE)) == NULL)
				buf.i = -1;
		if ((buf.size = read(fd, buf.buf, BUF_SIZE)) == -1)
			buf.i = -1;
	}
	return (buf);
}

int		read_line(char **line, t_buf buf)
{
	int		i;
	char	*save;

	i = 0;
	if ((save = ft_strnew(BUF_SIZE)) == NULL)
		return (-1);
	while (buf.i < buf.size)
	{
		if (buf.buf[buf.i] == '\n')
		{
			*line = ft_strjoingnl(*line, save);
			return (buf.i);
		}
		save[i] = buf.buf[buf.i];
		++i;
		++buf.i;
		if (buf.i == buf.size)
		{
			*line = ft_strjoingnl(*line, save);
			return (buf.i);
		}
	}
	return (buf.i);
}

int		get_next_line(int const fd, char **line)
{
	static t_buf	buf;

	if (!line)
		return (-1);
	buf = ft_realloc(fd, buf);
	if (buf.i == -1 || (*line = ft_strnew(0)) == NULL)
		return (-1);
	while (buf.size)
	{
		if (buf.buf[buf.i] == '\n')
		{
			++buf.i;
			return (1);
		}
		buf.i = read_line(line, buf);
		buf = ft_realloc(fd, buf);
		if (buf.i == -1)
			return (-1);
	}
	if (**line)
		return (1);
	return (0);
}
