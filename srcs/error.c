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

void	error(int n)
{
	static char	*msg[10] = {0, "Malloc failed\n",
							"Cant be more than 1 argument\n",
							"get next line error\n",
							"No spot\n",
							"file is invalid.\n",
							"No objects\n",
							"Failed to initialize SDL.\n",
							"Failed to create an SDL Window\n"};

	if (n > 0 && n < 9)
		ft_putstr_fd(msg[n], 2);
	exit(1);
}
