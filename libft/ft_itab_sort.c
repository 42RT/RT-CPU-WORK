/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itab_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 15:55:39 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:10:46 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_itab_sort(int *tab, size_t size)
{
	int		tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = 0;
	while (j < size)
	{
		while (i < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			i++;
		}
		i = 0;
		j++;
	}
}
