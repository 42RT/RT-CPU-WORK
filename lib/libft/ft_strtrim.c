/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:04:35 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/31 20:40:18 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <libft.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	char	*ptr;
	char	*result;

	if (!s || !*s)
		return (NULL);
	i = 0;
	ptr = (char *)(s - 1);
	while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
		++ptr;
	result = (char *)malloc(ft_strlen(ptr) * sizeof(char));
	ptr -= 1;
	i = -1;
	while (*++ptr)
		*(++i + result) = *ptr;
	ptr = i + result;
	while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
	{
		*ptr = '\0';
		--ptr;
	}
	return (result);
}
