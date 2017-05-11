/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 03:38:01 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/11 18:20:33 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <raytracer.h>
#include <parser.h>
#include <gui.h>

char	*get_obj_name(t_obj *obj)
{
	static char	**tbl = 0;
	char		**tmp;
	int			i;

	if (!(tmp = (char **)malloc(sizeof(char *) * 2)))
		error(1);
	if (!tbl)
	{
		tmp[0] = ft_strdup("sphere;plan;dplane;cylindre;cone;disk;square;");
		tmp[1] = ft_newstrcat(tmp[0], "cube;paraboloid;glass;");
		tbl = ft_strsplit(tmp[1], ';');
		gui_free_carray(&tmp, 2);
	}
	i = -1;
	while (++i < 10)
	{
		if (obj->type == (1 << i))
			return (tbl[i]);
	}
	return ("unknow");
}

void	save_objs(int fd, t_obj *obj)
{
	while (obj)
	{
		write_obj(fd, obj, 1);
		obj = obj->next;
		if (obj)
		{
			ft_putchar_fd(',', fd);
			ft_putstr_fd("\n\n", fd);
		}
	}
}

void	write_lights(int fd, t_light *light, int tab)
{
	ft_putstr_fd("\n\"light\": {\n", fd);
	write_light_attributes(fd, light, tab);
	ft_putstr_fd("}", fd);
}

void	save_lights(int fd, t_light *light)
{
	while (light)
	{
		write_lights(fd, light, 1);
		light = light->next;
		if (light)
			ft_putstr_fd(",\n", fd);
	}
}

int		save_scene(t_env *e)
{
	int		fd;
	char	*filename;

	filename = ft_newstrcat("scene/", e->scene);
	if (filename)
	{
		if ((fd = creat("scene/tmpsave.rts", O_CREAT | S_IRWXU |
		S_IRWXG | S_IRWXO)) != -1)
		{
			free(filename);
			save_objs(fd, e->obj);
			if (e->light)
				ft_putstr_fd(",\n", fd);
			save_lights(fd, e->light);
			ft_putchar_fd('\n', fd);
			close(fd);
			return (1);
		}
	}
	return (0);
}
