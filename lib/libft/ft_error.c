/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:55:30 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/07 09:48:11 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

INIT_PROGNAME;

int		ft_error(char const *s)
{
	ft_putstr_fd(PROGNAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(s, 2);
	return (0);
}
