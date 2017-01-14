/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/14 20:13:41 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	gui_expand_error(int n)
{
	n = 0;
}

void	gui_error(int n)
{
	printf("GUI ERROR : ");
	if (n == 1)
		printf("Unable to get display informations : %s\n", SDL_GetError());
	else if (n == 2)
		printf("Failed to Load BMP : %s\n", SDL_GetError());
	else if (n == 3)
		printf("Failed to Create texture : %s\n", SDL_GetError());
	else if (n == 4)
		printf("Failed to Create a Renderer : %s\n", SDL_GetError());
	else
		gui_expand_error(n);
	exit(1);
}
