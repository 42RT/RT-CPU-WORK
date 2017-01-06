/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 14:33:57 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/14 17:25:51 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;
	t_list	*newelem;

	if (lst)
		newlst = ft_lstmap(lst->next, f);
	if (!lst)
		return (NULL);
	newelem = f(lst);
	if (!(newlst = ft_lstnew(newelem->content, newelem->content_size)))
		return (NULL);
	ft_lstadd(&newlst, newlst);
	return (newlst);
}
