/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:27:19 by rfriscca          #+#    #+#             */
/*   Updated: 2017/02/09 15:09:32 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void			generate_noise(t_env *e)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < NOISE_HEIGHT)
	{
		while(j < NOISE_WIDTH)
		{
			e->noise[i][j] = (rand() % 32768) / 32768;
			++j;
		}
		j = 0;
		++i;
	}
}
