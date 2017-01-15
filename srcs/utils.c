/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 23:03:33 by jrouilly          #+#    #+#             */
/*   Updated: 2014/03/27 23:03:33 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>


unsigned int	limit_nb(unsigned int nb, unsigned int max)
{
	if (nb > max)
		nb = max;
	return (nb);
}

int				**new_base(void)
{
	int		**res;

	res = (int **)malloc(3 * sizeof(int *));
	res[0] = (int *)malloc(3 * sizeof(int));
	res[1] = (int *)malloc(3 * sizeof(int));
	res[2] = (int *)malloc(3 * sizeof(int));
	res[0][0] = 1;
	res[0][1] = 0;
	res[0][2] = 0;
	res[1][0] = 0;
	res[1][1] = 1;
	res[1][2] = 0;
	res[2][0] = 0;
	res[2][1] = 0;
	res[2][2] = 1;
	return (res);
}
