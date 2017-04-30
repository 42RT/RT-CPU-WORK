/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:14:20 by jrouilly          #+#    #+#             */
/*   Updated: 2017/04/27 13:14:22 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "includes/libft.h"

char	*ft_ftoa(float nb, int precision)
{
	char	*str;
	char	*entier;
	char	*decimal;
	char	*tmp;

	tmp = ft_itoa((int)nb);
	nb = nb - (int)nb;
	nb = nb * pow(10, precision);
	entier = ft_strjoin(tmp, ".");
	free(tmp);
	if (nb < 0)
		nb *= -1;
	decimal = ft_itoa((int)nb);
	str = ft_strjoin(entier, decimal);
	free(entier);
	free(decimal);
	return (str);
}
