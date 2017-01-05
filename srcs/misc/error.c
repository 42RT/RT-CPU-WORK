/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 13:19:38 by rfriscca          #+#    #+#             */
/*   Updated: 2016/10/12 16:44:12 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	expand_error(int n)
{
	if (n == 5)
	{
		ft_putstr("file is not valid\n");
		exit(1);
	}
	if (n == 6)
	{
		ft_putstr("No objects\n");
		exit(1);
	}
}

void	error(int n)
{
	if (n == 1)
	{
		ft_putstr("Malloc failed\n");
		exit(1);
	}
	else if (n == 2)
	{
		ft_putstr("Need 2 arguments\n");
		exit(1);
	}
	else if (n == 3)
	{
		ft_putstr("get next line error\n");
		exit(1);
	}
	else if (n == 4)
	{
		ft_putstr("No spot\n");
		exit(1);
	}
	else
		expand_error(n);
}
