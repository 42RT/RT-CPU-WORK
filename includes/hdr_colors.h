/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdr_colors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 00:21:49 by jrouilly          #+#    #+#             */
/*   Updated: 2017/03/12 00:21:50 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HDR_COLORS_H
# define HDR_COLORS_H

typedef struct		s_color
{
	unsigned		b	: 8;
	unsigned		g	: 8;
	unsigned		r	: 8;
	unsigned		a	: 8;
	int				e	: 8;
}					t_color;

/*
** Additions (aren't HDR for the moment)
*/
void				color_add(t_color *src, t_color color,
								unsigned int k);
t_color				mix_color(t_color c1, t_color c2);
void				color_mix_k(t_color *src, t_color color,
							unsigned int k);

/*
** Convert
*/
t_color				rgb_to_tcolor(unsigned int r, unsigned int g,
									unsigned int b);
t_color				int_to_tcolor(unsigned int color);
unsigned int		tcolor_to_int(t_color color);
t_color				get_color(char *str);

/*
** Tests and init
*/
t_color				void_tcolor(void);
int					is_void_tcolor(t_color color);

/*
** Various
*/
t_color				color_attenuate(t_color color, float k);

#endif
