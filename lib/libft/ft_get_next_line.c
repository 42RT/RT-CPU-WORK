/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 21:59:44 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/29 21:59:54 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libft.h>

static int	get_next_loop(int *tbl, int *nb, char **line, char **buff)
{
	int		ret;
	char	*temp;

	temp = NULL;
	tbl[1] = 0;
	temp = *line;
	*line = (char *)malloc(((++*nb + 1) * BUFF_SIZE + 1) * sizeof(char));
	if (*line == NULL)
		return (-1);
	ft_strncpy(*line, temp, *nb * BUFF_SIZE);
	if (temp != NULL)
		free(temp);
	ret = read(tbl[2], *buff, BUFF_SIZE);
	if (ret > 0)
	{
		*(*buff + ret) = '\0';
		while (*(*buff + tbl[1]) != '\0' && *(*buff + tbl[1]) != '\n'
				&& tbl[1] < BUFF_SIZE)
		{
			*(*line + tbl[0] + tbl[1]) = *(*buff + tbl[1]);
			++tbl[1];
		}
		tbl[0] += tbl[1];
	}
	return (ret);
}

static int	get_next_return(int fd, int ret, char **buff, char **line)
{
	int		nb;
	int		tbl[3];

	if (ret == 0)
		return (0);
	nb = 0;
	tbl[1] = 0;
	tbl[2] = fd;
	while (*(*buff + tbl[1]) != '\0' && *(*buff + tbl[1]) != '\n'
			&& tbl[1] < BUFF_SIZE)
	{
		*(*line + tbl[1]) = *(*buff + tbl[1]);
		++tbl[1];
	}
	tbl[0] = tbl[1];
	*(*line + tbl[1]) = '\0';
	while ((*(*buff + tbl[1]) != '\n') && (ret > 0))
	{
		ret = get_next_loop(tbl, &nb, line, buff);
	}
	ret = ((*(*buff + (tbl[0] % BUFF_SIZE)) != '\0') || ret == BUFF_SIZE);
	ft_strcpy(*buff, *buff + tbl[1] + 1);
	return (ret != 0);
}

int			get_next_line(int const fd, char **line)
{
	static char	*buff[24];
	int			ret;

	if (BUFF_SIZE < 1)
		return (-1);
	*line = (char *)malloc((BUFF_SIZE + 1) * sizeof(char));
	if (buff[fd] == NULL)
	{
		buff[fd] = (char *)malloc((BUFF_SIZE + 2) * sizeof(char));
		if (buff[fd] == NULL)
			return (-1);
		*(buff[fd] + BUFF_SIZE) = '\0';
		*(buff[fd] + BUFF_SIZE + 1) = '\0';
		ret = read(fd, buff[fd], BUFF_SIZE);
		*(buff[fd] + ret) = '\0';
	}
	ret = get_next_return(fd, 1, &(buff[fd]), line);
	if ((ret == 0) && (buff[fd] != NULL))
	{
		free(buff[fd]);
		buff[fd] = NULL;
	}
	return (ret);
}
