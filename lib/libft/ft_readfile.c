/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/15 01:39:44 by jrouilly          #+#    #+#             */
/*   Updated: 2014/10/15 01:40:02 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

char		*ft_readfile(int fd)
{
	char	buff[RD_BUFFSIZE + 1];
	char	*res;
	char	*old;
	int		i;

	i = 0;
	buff[RD_BUFFSIZE] = 0;
	res = (char *)malloc(sizeof(char));
	*res = 0;
	while (read(fd, buff, RD_BUFFSIZE) > 0)
	{
		old = res;
		res = (char *)malloc((RD_BUFFSIZE * ++i + 1) * sizeof(char));
		ft_strcpy(res, old);
		ft_strcat(res, buff);
		free(old);
	}
	return (res);
}
