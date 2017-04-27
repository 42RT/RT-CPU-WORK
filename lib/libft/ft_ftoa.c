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

	str = ft_itoa((int)nb);
	nb = nb - (int)nb;
	nb = nb * pow(10, precision);
	str = ft_strjoin(str, ".");
	str = ft_strjoin(str, ft_itoa((int)nb));
	return (str);
}
