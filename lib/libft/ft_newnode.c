/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 16:07:31 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/15 16:15:51 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree	*ft_newnode(void const *content, size_t content_size)
{
	t_tree	*newnode;

	if ((newnode = (t_tree*)malloc((sizeof(*newnode)))) == NULL)
		return (NULL);
	if (content == 0)
	{
		newnode->content = NULL;
		newnode->content_size = 0;
	}
	else
	{
		if ((newnode->content = (void*)malloc(content_size)) == NULL)
			return (NULL);
		ft_memmove(newnode->content, content, content_size);
		newnode->content_size = content_size;
	}
	newnode->right = NULL;
	newnode->left = NULL;
	return (newnode);
}
