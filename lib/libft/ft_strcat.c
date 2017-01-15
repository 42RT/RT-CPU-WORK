/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:56:49 by jrouilly          #+#    #+#             */
/*   Updated: 2013/12/31 20:38:17 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, const char *src)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = (char *)dest;
	while (*(dest + j))
		++j;
	while (*(src + i))
	{
		*(dest + j) = *(src + i);
		++i;
		++j;
	}
	*(dest + j) = '\0';
	return (result);
}
