/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 17:05:06 by tjarross          #+#    #+#             */
/*   Updated: 2017/01/06 14:05:17 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVEC_H
# define LIBVEC_H

# include <math.h>

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

t_vec			normalize(t_vec v);
float			dot(t_vec v1, t_vec v2);
float			get_dist(t_vec v);
t_vec			rot(t_vec v, float hor_angle, float vert_angle);
t_vec			multiply_vec(t_vec v, float n);
t_vec			sub_vec(t_vec v1, t_vec v2);
t_vec			add_vec(t_vec v1, t_vec v2);
t_vec			div_vec(t_vec v1, float n);
t_vec			dot_div(t_vec v1, t_vec v2);
t_vec			not_vec(t_vec v);
t_vec			get_inters(t_vec origin, t_vec raydir, float t);
t_vec			product_vec(t_vec v1, t_vec v2);
t_vec			reflect_vec(t_vec dir, t_vec n);
t_vec			rotvec(t_vec vec, t_vec trans);
t_vec			rotx(t_vec vec, float angle);
t_vec			roty(t_vec vec, float angle);
t_vec			rotz(t_vec vec, float angle);
t_vec			calc_vec(t_vec p1, t_vec p2);

#endif
