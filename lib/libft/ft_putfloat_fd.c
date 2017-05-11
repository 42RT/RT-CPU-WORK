/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:56:01 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/11 18:14:25 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putfloat_fd(float n, int precision, int fd)
{
	ft_putstr_fd(ft_ftoa(n, precision), fd);
}
