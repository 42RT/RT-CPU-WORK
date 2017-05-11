/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 16:02:31 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/06 17:41:53 by vcaquant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtdefs.h>
#include <parser.h>
#include <unistd.h>
#include <fcntl.h>

void		ft_check_valid_file(char *str)
{
	int		fd;
	int		i;
	int		r;
	char	buf[4096];

	if ((fd = open(str, O_RDONLY)) == -1)
		parse_error();
	while ((r = read(fd, buf, 4096)) > 0)
	{
		i = -1;
		while (++i < r)
		{
			if (!buf[i])
			{
				close(fd);
				parse_error();
			}
		}
	}
	if (r == -1)
		parse_error();
	close(fd);
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

void		verif_obj_validity(t_obj *obj)
{
	if (obj->pos.x > 99999 || obj->pos.x < -99999)
		obj->pos.x = DEF_OBJ_POSX;
	if (obj->pos.y > 99999 || obj->pos.y < -99999)
		obj->pos.y = DEF_OBJ_POSY;
	if (obj->pos.z > 99999 || obj->pos.z < -99999)
		obj->pos.z = DEF_OBJ_POSZ;
	if (obj->ang.x > 180 * M_PI_2 / 90 || obj->ang.x < -180 * M_PI_2 / 90)
		obj->ang.x = DEF_OBJ_ANGX;
	if (obj->ang.y > 180 * M_PI_2 / 90 || obj->ang.y < -180 * M_PI_2 / 90)
		obj->ang.y = DEF_OBJ_ANGY;
	if (obj->ang.z > 180 * M_PI_2 / 90 || obj->ang.z < -180 * M_PI_2 / 90)
		obj->ang.z = DEF_OBJ_ANGZ;
	if (obj->size > 9999)
		obj->size = DEF_SIZE;
	if (obj->transparency > 255 || obj->transparency < 0)
		obj->transparency = MIN_REFRACT_K;
	if (obj->reflect_k > 255 || obj->reflect_k < 0)
		obj->reflect_k = MIN_REFLECT_K;
	if (obj->refract_ind > 4 || obj->refract_ind < 1)
		obj->refract_ind = MIN_REFRACT_IND;
}

void		parse_distrib(t_env *e, t_item *item)
{
	int		i;

	i = -1;
	if (!item)
		parse_error();
	else if (!ft_strncmp(item->type, "\"settings\"", 10))
		parse_settings(e, item, i);
	else if (!ft_strncmp(item->type, "\"light\"", 7))
		parse_light(e, item);
	else if (obj_gettype(item->type) != NONE)
		parse_object(e, item);
	else
		ft_printf("\033[31m%s Not found\n\033[0m", item->type);
	while (++i < item->setnb)
		free(item->set[i]);
	free(item->type);
	free(item);
}

void		parse(t_env *e, char *filename)
{
	char	*file;
	t_item	*item;

	ft_check_valid_file(filename);
	first_chek(e, filename);
	file = ft_getfile(filename);
	e->file = file;
	if (!file)
		parse_error();
	while (file && *file)
	{
		if ((item = get_next_item(&file)) == NULL)
			parse_error();
		parse_distrib(e, item);
	}
	verif_set_validity(e);
	secu_neg_obj(e->obj);
	ft_printf("File \"%s\" parsed.\n", filename);
	free(e->file);
}
