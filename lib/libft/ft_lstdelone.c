/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 17:50:06 by rdieulan          #+#    #+#             */
/*   Updated: 2016/03/02 14:49:21 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstdelone(t_list **alst, void *content)
{
	t_list	*temp;
	t_list	*previous;

	temp = *alst;
	previous = NULL;
	while (temp)
	{
		if (temp->content == content)
		{
			if (previous == NULL)
				*alst = temp->next;
			else
				previous->next = temp->next;
			free(temp->content);
			free(temp);
			temp = NULL;
			return ;
		}
		previous = temp;
		temp = temp->next;
	}
}
