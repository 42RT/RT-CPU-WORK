/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/19 19:11:46 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/19 19:12:25 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libxmlx.h>
#include <raytracer.h>

int		expose_hook(t_env *e)
{
	libxmlx_blitz_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
	libxmlx_flip_screen(e->gfx);
	return (0);
}
