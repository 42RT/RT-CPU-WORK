/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:02:31 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/11 16:02:32 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>

void	verif_set_validity(t_env *e)
{
	if (e->set->height < MIN_DEF_Y)
		e->set->height = MIN_DEF_Y;
	if (e->set->width < MIN_DEF_X)
		e->set->width = MIN_DEF_X;
	if (e->set->height > MAX_DEF_Y)
		e->set->height = MAX_DEF_Y;
	if (e->set->width > MAX_DEF_X)
		e->set->width = MAX_DEF_X;
}

void	parse(t_env *e, char *filename)
{
	char	*file;
	t_item	*item;

	file = ft_getfile(filename);
	if (!file)
		return ;
	while (file && *file)
	{
		item = get_next_item(&file);
		if (!item)
			break ;
		else if (!strncmp(item->type, "setting", ft_strlen("setting")))
			parse_settings(e, item);
		else if (!strncmp(item->type, "light", ft_strlen("light")))
			parse_light(e, item);
		else
		{
			parse_object(e, item);
		}
	}
	verif_set_validity(e);
	ft_printf("File \"%s\" parsed.\n", filename);
}
