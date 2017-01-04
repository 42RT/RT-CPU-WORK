/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:20:43 by rdieulan          #+#    #+#             */
/*   Updated: 2016/03/15 15:48:40 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "includes/libft.h"

# define BUFF_SIZE	20

typedef struct	s_file
{
	char	*file_content;
	int		fd;
}				t_file;

int				get_next_line(int const fd, char **line);

#endif
