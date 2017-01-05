/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 13:48:55 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/10 14:07:51 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_line	*ft_new_line(char *line, int size)
{
	t_line	*file;
	int		i;

	i = 0;
	if ((file = (t_line*)malloc(sizeof(*file))) == NULL)
		error(1);
	if ((file->line = ft_strnew(size)) == NULL)
		error(1);
	file->next = NULL;
	while (i < size)
	{
		file->line[i] = line[i];
		++i;
	}
	file->size = size;
	free(line);
	return (file);
}
