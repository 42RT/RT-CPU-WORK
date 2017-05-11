/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_distrib_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaquant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:36:40 by vcaquant          #+#    #+#             */
/*   Updated: 2017/05/11 18:16:46 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <raytracer.h>
#include <parser.h>

void	save_dis_nbr_nocoma(float obj, char *str, int fd, int tab)
{
	write_padding(fd, tab);
	ft_putstr_fd("\"", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\": ", fd);
	ft_putfloat_fd(obj, 1, fd);
	ft_putstr_fd("\n", fd);
}

void	save_dis_color(t_color color, int fd, int tab)
{
	write_padding(fd, tab);
	ft_putstr_fd("\"rgb\": {\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"r\": ", fd);
	ft_putnbr_fd(color.r, fd);
	ft_putstr_fd(",\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"g\": ", fd);
	ft_putnbr_fd(color.g, fd);
	ft_putstr_fd(",\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"b\": ", fd);
	ft_putnbr_fd(color.b, fd);
	ft_putchar_fd('\n', fd);
	write_padding(fd, tab);
	ft_putstr_fd("},", fd);
	ft_putchar_fd('\n', fd);
}

void	save_dis_compose(t_obj *obj, int fd, int tab)
{
	write_padding(fd, tab);
	ft_putstr_fd("\"compose\": {\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"", fd);
	ft_putstr_fd(get_obj_name(obj), fd);
	ft_putstr_fd("\": {\n", fd);
	write_obj_attributes(fd, obj, tab + 2);
	write_padding(fd, tab + 1);
	ft_putstr_fd("}\n", fd);
	write_padding(fd, tab);
	ft_putstr_fd("},\n", fd);
}

void	save_dis_next(t_obj *obj, int fd, int tab)
{
	while (obj->next != NULL)
	{
		save_dis_compose(obj->next, fd, tab);
		obj = obj->next;
	}
}
