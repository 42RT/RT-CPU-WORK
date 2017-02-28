/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 13:19:38 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/14 18:19:43 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	expand_error(int n)
{
	(void)n;
}

void	error(int n)
{
	if (n == 1)
		ft_putstr("Malloc failed\n");
	else if (n == 2)
		ft_putstr("Need 2 arguments\n");
	else if (n == 3)
		ft_putstr("get next line error\n");
	else if (n == 4)
		ft_putstr("No spot\n");
	else if (n == 5)
		ft_putstr("file is invalid.\n");
	else if (n == 6)
		ft_putstr("No objects\n");
	else if (n == 7)
		ft_putstr("Failed to initialize SDL.\n");
	else if (n == 8)
		ft_putstr("Failed to create an SDL Window\n");
	else
		expand_error(n);
	exit(1);
}
