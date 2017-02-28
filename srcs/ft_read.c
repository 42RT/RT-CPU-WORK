/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelprat <tdelprat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 13:32:18 by tdelprat          #+#    #+#             */
/*   Updated: 2014/03/27 16:14:23 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <raytracer.h>

/*
t_obj				*ft_addobj(t_obj *obj, t_obj obj_tmp, int type)
{
	t_obj			*new;
	t_obj			*tmp;

	new = (t_obj *)malloc(sizeof(t_obj));
	if (new == NULL)
		return (obj);
	new->type = type;
	new->func = get_func(type);
	new->normale = get_normale(type);
	new->pos.x = obj_tmp.pos.x;
	new->pos.y = obj_tmp.pos.y;
	new->pos.z = obj_tmp.pos.z;
	new->color = obj_tmp.color;
	new->color2 = obj_tmp.color2;
	new->color3 = obj_tmp.color3;
	new->diffusion_k = 255;
	new->reflect_k = 255;
	new->size = obj_tmp.size;
	new->base = new_base();
	new->next = NULL;
	if (obj == NULL)
		return (new);
	else
	{
		tmp = obj;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (obj);
}

void				create_scene(t_struct *ts, char *title, char *size)
{
	char			**size_tab;

	ts->title = title;
	size_tab = ft_strsplit(size, ',');
	if (!size_tab || !size_tab[0] || !size_tab[1] || !size_tab[2])
		ft_err("error: strsplit\n");
	ts->res_x = ft_atoi(size_tab[0]);
	ts->res_y = ft_atoi(size_tab[1]);
	ts->aa = ft_atoi(size_tab[2]);
	ts->deph = 2;
}

void				ft_set_second_cam(t_struct *ts)
{
	ts->cam.angle2.x = ts->cam.angle.x;
	ts->cam.angle2.y = ts->cam.angle.y;
	ts->cam.angle2.z = ts->cam.angle.z;
	rotate_vector(&(ts->cam.angle2), 0, ts->cam.d3_angle * M_PI / 180, 0);
	ts->cam.pos2.x = ts->cam.pos.x + ts->cam.d3_offset;
	ts->cam.pos2.y = ts->cam.pos.y;
	ts->cam.pos2.z = ts->cam.pos.z;
}

void				create_camera(t_struct *ts, char *coor)
{
	char			**coor_tab;

	coor_tab = ft_strsplit(coor, ',');
	if (!coor_tab || !coor_tab[0] || !coor_tab[1] || !coor_tab[2]
		|| !coor_tab[3] || !coor_tab[4] || !coor_tab[5] || !coor_tab[6])
		ft_err("error: strsplit\n");
	ts->cam.pos.x = ft_atoi(coor_tab[0]);
	ts->cam.pos.y = ft_atoi(coor_tab[1]);
	ts->cam.pos.z = ft_atoi(coor_tab[2]);
	ts->cam.angle.x = (ft_atoi(coor_tab[3]) * M_PI) / 180;
	ts->cam.angle.y = (ft_atoi(coor_tab[4]) * M_PI) / 180;
	ts->cam.angle.z = (ft_atoi(coor_tab[5]) * M_PI) / 180;
	ts->cam.fov = M_PI_2 * 0.7;
	ts->cam.ratio = (float)ts->res_y / (float)ts->res_x;
	ts->cam.d3_enabled = ft_atoi(coor_tab[6]);
	ts->cam.d3_offset = 20;
	ts->cam.d3_angle = 15;
	if (ts->cam.d3_enabled)
		ft_set_second_cam(ts);
}

void				create_light(t_struct *ts, char *coor, char *power)
{
	t_light			*obj;
	t_light			*tmp;
	char			**coor_tab;

	obj = (t_light *)malloc(sizeof(t_light));
	if (obj == NULL)
		return ;
	obj->k1 = ft_atoi(power);
	coor_tab = ft_strsplit(coor, ',');
	obj->pos.x = ft_atoi(coor_tab[0]);
	obj->pos.y = ft_atoi(coor_tab[1]);
	obj->pos.z = ft_atoi(coor_tab[2]);
	tmp = ts->light;
	if (tmp == NULL)
		ts->light = obj;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = obj;
	}
	++ts->nb_light;
}

t_struct			*ft_read(t_obj **obj, int fd)
{
	char			**tab;
	char			*line;
	int				ret;
	t_struct		*ts;

	ts = get_struct();
	ret = 1;
	ts->light = 0;
	ts->nb_light = 0;
	while (ret > 0)
	{
		ret = ft_get_next_line(fd, &line);
		tab = ft_strsplit(line, ' ');
		if (tab[0] == NULL || !ft_strcmp(tab[0], "#"))
			continue;
		if (!ft_strcmp(tab[0], "scene"))
			create_scene(ts, tab[2], tab[3]);
		else if (!ft_strcmp(tab[0], "camera"))
			create_camera(ts, tab[2]);
		else if (!ft_strcmp(tab[0], "sphere"))
			*obj = create_sphere(*obj, tab[2], tab[3], tab[4]);
		else if (!ft_strcmp(tab[0], "cylinder"))
			*obj = create_cylinder(*obj, tab[2], tab[3], tab[4]);
		else if (!ft_strcmp(tab[0], "floor"))
			*obj = create_floor(*obj, tab[2], tab[3]);
		else if (!ft_strcmp(tab[0], "dfloor"))
			*obj = create_dfloor(*obj, tab[2], tab[3], tab[4], tab[5]);
		else if (!ft_strcmp(tab[0], "light"))
			create_light(ts, tab[2], tab[3]);
		else if (!ft_strcmp(tab[0], "square"))
			*obj = create_square(*obj, tab[2], tab[3]);
		else
			ft_err("rtv1: wrong scene descriptor syntax\n");
	}
	return (ts);
}
*/