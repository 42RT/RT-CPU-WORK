/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 17:32:04 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_expand_error2(int n)
{
	(void)n;
}

void	gui_expand_error(int n)
{
	if (n == 11)
		ft_printf("PARSE : \033[31mExpected widget delimiter ','\033[0m\n");
	else if (n == 12)
		ft_printf("PARSE \033[31mNot the widget expected\033[0m\n");
	else if (n == 13)
		ft_printf("PARSE \033[31mImpossible to open directory. \033[0m\n");
	else if (n == 14)
		ft_printf("PARSE \033[31mImpossible to close directory. \033[0m\n");
	else if (n == 15)
		ft_printf("PARSE : \033[31mCannot Create file.\033[0m : %d\n", errno);
	else if (n == 16)
		ft_printf("PARSE : \033[31mWidget property doesnt match\033[0m\n");
	else if (n == 17)
		ft_printf("PARSE : \033[31mForbidden widget value\033[0m\n");
	else
		gui_expand_error2(n);
}

void	gui_error(int n)
{
	if (n == 1)
		ft_printf("Unable to get display informations : %s\n", SDL_GetError());
	else if (n == 2)
		ft_printf("Failed to Load BMP : %s\n", SDL_GetError());
	else if (n == 3)
		ft_printf("Failed to Create texture : %s\n", SDL_GetError());
	else if (n == 4)
		ft_printf("Failed to Create a Renderer : %s\n", SDL_GetError());
	else if (n == 5)
		ft_printf("\033[31mFailed\033[0m : %s\n", SDL_GetError());
	else if (n == 6)
		ft_printf("Failed to load Font : %s\n", SDL_GetError());
	else if (n == 7)
		ft_printf("AA : %s\n", SDL_GetError());
	else if (n == 8)
		ft_printf("PARSE : \033[31mEmpty File.\033[0m\n");
	else if (n == 9)
		ft_printf("PARSE : \033[31mCannot Open file.\033[0m\n");
	else if (n == 10)
		ft_printf("PARSE : \033[31mExpected container delimiter ','\033[0m\n");
	else
		gui_expand_error(n);
	exit(1);
}
