/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 03:38:01 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 03:38:01 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <parser.h>

char	*get_obj_name(obj->type)
{
	static char	**tbl = 0;
	char		*tmp[2];
	int			i;

	if (!tbl)
	{
		tmp[0] = ft_strdup("sphere;plane;dplane;cylinder;cone;disk;square;");
		tmp[1] = ft_newstrcat(tmp[0], "paraboloid;glass");
		tbl = ft_strsplit(tmp[1], ';');
		free(tmp[0]);
		free(tmp[1]);
	}
	i = -1;
	while (++i < 9)
	{
		if (obj->type == (1 << i))
			return (tbl[i]);
	}
	return ("unknow");
}

void	write_padding(int fd, int nb)
{
	int		i;

	i = -1;
	while (++i < nb)
		ft_putchar_fd('\t', fd);
}

void	write_obj_attributes(int fd, t_obj *obj, int tab)
{
	write_padding(fd, tab);

}

void	write_obj(int fd, t_obj *obj, int tab)
{
	write_padding(fd, tab);
	ft_printf_fd("\"%s\": {\n", get_obj_name(obj->type));
	write_obj_attributes(fd, obj, tab + 1);
	write_padding(fd, tab);
	ft_putstr_fd("}\n", fd);
}

void	save_objs(int fd, t_obj *obj)
{
	while (obj)
	{
		write_obj(fd, obj, 0);
		obj = obj->next;
		if (obj)
		{
			ft_putchar_fd(',', fd);
			ft_putchar_fd('\n', fd);
		}
	}
}

void	save_lights(int fd, t_light *light)
{
	while (light)
	{
		write_obj(fd, obj, 1);
		light = light->next;
		if (light)
		{
			ft_putchar(',');
			ft_putchar('\n');
		}
	}
}

int		save_scene(t_env *e)
{
	char	*filename;

	filename = ft_newstrcat("scenes/", e->scene);
	if (filename)
	{
		if ((fd = creat("scene/tmpsave.rts", O_CREAT | S_IRWXU |
		S_IRWXG | S_IRWXO)) != -1)
		{
			free(filename);
			save_objs(fd, e->obj);
			if (e->light)
			{
				ft_putchar(',');
				ft_putchar('\n');
			}
			save_lights(fd, e->light);
			ft_putchar('\n');
			close(fd);
			return (1);
		}
	}
	return (0);
}