/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebladi <jdebladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 19:14:49 by jdebladi          #+#    #+#             */
/*   Updated: 2016/12/02 14:11:00 by jdebladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "includes/libft.h"

# define BUFF_SIZE 32

typedef struct	s_file
{
	char	*file_content;
	int		fd;
}				t_file;

int				get_next_line(const int fd, char **line);

#endif
