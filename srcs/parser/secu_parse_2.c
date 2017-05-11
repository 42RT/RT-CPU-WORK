/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secu_parse_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 18:18:21 by rfriscca          #+#    #+#             */
/*   Updated: 2017/05/11 18:18:24 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	secu_neg_obj(t_obj *obj)
{
	t_obj	*first;
	int		i;

	i = 0;
	first = obj;
	while (obj)
	{
		if (obj->negative == 0)
			++i;
		obj = obj->next;
	}
	if (i == 0)
	{
		ft_putstr("No object\n");
		exit(EXIT_SUCCESS);
	}
	obj = first;
}
