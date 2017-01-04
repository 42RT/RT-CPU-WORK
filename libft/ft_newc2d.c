/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newc2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 16:08:42 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:14:21 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	**ft_newc2d(size_t i, size_t j, char c)
{
	size_t	k;
	char	**tab;

	k = 0;
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	while (k < j)
	{
		tab[k] = (char *)malloc(sizeof(char) * j);
		ft_memset(tab[k], c, j);
		k++;
	}
	tab[k] = (char *)malloc(sizeof(char) * 1);
	tab[i][0] = '\0';
	return (tab);
}
