/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:01:36 by jrouilly          #+#    #+#             */
/*   Updated: 2017/03/08 11:01:45 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <raytracer.h>

static void	ft_zero_fill(char *str, int n)
{
	while (--n >= 0)
		str[n] = 0;
}

void		ft_itos(unsigned int i, char *s)
{
	s[0] = i & 0xFF;
	s[1] = (i >> 8) & 0xFF;
	s[2] = (i >> 16) & 0xFF;
	s[3] = (i >> 24) & 0xFF;
}

static void	write_header(int fd, int w, int h)
{
	char	header[54];

	ft_zero_fill(header, 54);
	header[0] = 66;
	header[1] = 77;
	ft_itos(h * w * 4 + 54, header + 2);
	header[10] = 54;
	header[14] = 40;
	ft_itos(w, header + 18);
	ft_itos(h, header + 22);
	header[26] = 1;
	header[28] = 32;
	ft_itos(h * w * 4, header + 34);
	ft_itos(72, header + 38);
	ft_itos(72, header + 42);
	write(fd, header, 54);
}

/*
** care about endian
*/

static void	write_pixels(int fd, int w, int h, t_img *img)
{
	int				y;
	int				x;
	unsigned int	*map;

	if (!(map = (unsigned int *)malloc(w * h * sizeof(unsigned int))))
		error(1);
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			map[w * y + x] = *(unsigned int *)(img->data + w * (h - 1 - y)
												+ x);
	}
	write(fd, map, w * h * 4);
	free(map);
}

int			save_image(t_img *img, char *name)
{
	int			fd;
	char		*path;

	if (!*name)
		return (ft_error("Please enter a filename !"));
	path = ft_newstrcat("screenshots/", name);
	free(name);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(path);
	if (!fd)
		return (ft_error("Unable to create file :("));
	write_header(fd, img->width, img->height);
	write_pixels(fd, img->width, img->height, img);
	close(fd);
	return (0);
}
