/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 03:31:49 by rdieulan          #+#    #+#             */
/*   Updated: 2016/11/23 03:31:50 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libvec.h>

t_vec	get_inters(t_vec origin, t_vec raydir, float t)
{
	return (add_vec(origin, multiply_vec(raydir, t)));
}
