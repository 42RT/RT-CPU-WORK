/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 12:20:10 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/21 14:47:48 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	errortest(char *line, int ret)
{
	if (ret == -1)
		error(3);
	if (!line[0])
		error(5);
}

t_line	*save_file(int fd)
{
	int		ret;
	t_line	*file_start;
	t_line	*file;
	char	*line;
	int		i;

	file_start = NULL;
	i = 0;
	if ((ret = get_next_line(fd, &line)) == -1)
		error(3);
	if ((file_start = ft_new_line(line, ft_strlen(line))) == NULL)
		error(3);
	file = file_start;
	ret = get_next_line(fd, &line);
	errortest(line, ret);
	while (ret > 0)
	{
		file->next = ft_new_line(line, ft_strlen(line));
		file = file->next;
		if ((ret = get_next_line(fd, &line)) == -1)
			error(3);
		++i;
	}
	free(line);
	return (file_start);
}
