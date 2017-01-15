/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_trim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 08:38:13 by jrouilly          #+#    #+#             */
/*   Updated: 2014/11/28 08:38:13 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup_trim(char *str)
{
	while (*str && (*str == ' ' || *str == '\n' || *str == '\r' || *str == '\t'))
		++str;
	if (!str)
		return (0);
	return (ft_strndup(str, ft_strlen_trim(str)));
}