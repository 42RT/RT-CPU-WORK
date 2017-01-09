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
