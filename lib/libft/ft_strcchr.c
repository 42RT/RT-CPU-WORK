/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:28:28 by vcaquant          #+#    #+#             */
/*   Updated: 2017/02/22 13:29:03 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>

char	*ft_strcchr(const char *s, int c, int f)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c && s[i] != f)
		i++;
	if (s[i] == c)
		return ((char*)&s[i]);
	return (NULL);
}
