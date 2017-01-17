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
#include <unistd.h>
#include <fcntl.h>

static int	ft_check_valid_file(char *str)
{
	int		fd;
	int		i;
	int		r;
	char	buf[4096];

	fd = open(str, O_RDONLY);
	while ((r = read(fd, buf, 4096)) > 0)
	{
		i = -1;
		while (++i < r)
		{
			if (!buf[i])
			{
				close(fd);
				return (0);
			}
		}
	}
	close(fd);
	return (1);
}

void		verif_set_validity(t_env *e)
{
	if (e->set->height < MIN_DEF_Y)
		e->set->height = MIN_DEF_Y;
	else if (e->set->height > MAX_DEF_Y)
		e->set->height = MAX_DEF_Y;
	if (e->set->width < MIN_DEF_X)
		e->set->width = MIN_DEF_X;
	else if (e->set->width > MAX_DEF_X)
		e->set->width = MAX_DEF_X;
	if (e->set->threads > MAX_THREADS)
		e->set->threads = MAX_THREADS;
	if (e->set->threads < 1)
		e->set->threads = 1;
	if (e->set->fov < 10)
		e->set->fov = 10;
	if (e->set->fov > 170)
		e->set->fov = 170;
}

void		parse(t_env *e, char *filename)
{
	char	*file;
	t_item	*item;

	if (!ft_check_valid_file(filename))
		return ;
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
			parse_object(e, item);
	}
	verif_set_validity(e);
	ft_printf("File \"%s\" parsed.\n", filename);
}
