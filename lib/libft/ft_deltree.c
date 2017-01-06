/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 16:39:59 by rfriscca          #+#    #+#             */
/*   Updated: 2015/12/15 16:47:35 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_deltree(t_tree *node)
{
	if (node->left)
		ft_deltree(node->left);
	if (node->right)
		ft_deltree(node->right);
	ft_delnode(node);
}
