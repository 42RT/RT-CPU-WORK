/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:55:30 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/15 15:56:42 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

extern const char *__progname;

int		ft_error(char const *s)
{
	ft_putstr_fd(__progname, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(s, 2);
	return (-1);
}
