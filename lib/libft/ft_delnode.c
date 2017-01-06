/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 16:36:23 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/16 11:30:11 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delnode(t_tree *node)
{
	ft_bzero(node->content, node->content_size);
	free(node->content);
	node->content = NULL;
	node->content_size = 0;
	free(node);
	node = NULL;
}
