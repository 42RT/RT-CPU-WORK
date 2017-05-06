/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdr_colors_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 00:22:41 by jrouilly          #+#    #+#             */
/*   Updated: 2017/03/12 00:22:42 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hdr_colors.h>

t_color		void_tcolor(void)
{
	t_color	res;

	res.r = 0;
	res.g = 0;
	res.b = 0;
	res.e = 0;
	res.a = 0xFF;
	return (res);
}

int			is_void_tcolor(t_color color)
{
	return (!(color.r || color.g || color.b));
}
