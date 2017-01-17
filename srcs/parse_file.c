/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 15:50:21 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/11 15:50:22 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

char		*ft_getfile(char *name)
{
	int		fd;
	char	*res;

	if (!name || !*name)
		return (0);
	fd = open(name, O_RDONLY);
	res = ft_readfile(fd);
	close(fd);
	return (res);
}
