/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 12:56:20 by jrouilly          #+#    #+#             */
/*   Updated: 2013/11/26 19:22:40 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	if ((!s1 || !*s1) && *s2)
		return (-1);
	else if ((!s2 || !*s2) && *s1)
		return (1);
	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	while (*ptrs1 && *ptrs2)
	{
		if (*ptrs1 > *ptrs2)
			return (1);
		else if (*ptrs1 < *ptrs2)
			return (-1);
		else
		{
			++ptrs1;
			++ptrs2;
		}
	}
	return (0 + (*ptrs1 != 0) - (*ptrs2 != 0));
}
