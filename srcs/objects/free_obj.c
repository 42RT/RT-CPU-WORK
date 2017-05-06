/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:32:40 by rfriscca          #+#    #+#             */
/*   Updated: 2017/05/06 14:32:49 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	free_obj(t_obj *obj)
{
	if (obj->texture)
		free(obj->texture);
	if (obj->normalmap)
		free(obj->normalmap);
	if (obj->procedural)
		free(obj->procedural);
	free(obj);
}

void	destroy_obj_list(t_obj *obj)
{
	if (obj->compose)
		destroy_obj_list(obj->compose);
	if (obj->next)
		destroy_obj_list(obj->next);
	if (obj)
		free_obj(obj);
}
