/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:54:07 by rdieulan          #+#    #+#             */
/*   Updated: 2016/02/15 16:17:39 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cp;

	cp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (cp == NULL)
		return (NULL);
	ft_strcpy(cp, s1);
	return (cp);
}
