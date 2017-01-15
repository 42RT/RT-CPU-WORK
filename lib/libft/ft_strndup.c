/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 08:35:36 by jrouilly          #+#    #+#             */
/*   Updated: 2014/11/28 08:35:36 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(char *str, size_t len)
{
	char	*res;

	res = ft_strnew(len + 1);
	ft_strncpy(res, str, len);
	return (res);
}
