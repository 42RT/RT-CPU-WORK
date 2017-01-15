/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 15:26:42 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/15 15:02:54 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tab_alloc(int l, int c)
{
	char	**tab;
	int		i;

	i = 0;
	if ((tab = (char**)malloc(sizeof(tab) * l + 1)) == NULL)
		return (NULL);
	while (i < l)
	{
		if ((tab[i] = ft_strnew(c)) == NULL)
			return (NULL);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
