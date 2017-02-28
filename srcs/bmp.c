/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 17:59:39 by rmorel            #+#    #+#             */
/*   Updated: 2014/12/16 17:59:41 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmp.h>

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

/*static void	write_pixels(int fd, int w, int h, char *array)//modifier pour sdl2
{
	int y;

	y = -1;
	while (++y < h)
		write(fd, array + ((h - 1 - y) * w * 4), w * 4);
}*/

void		save_image(void *img, char *name, t_img *param)
{
	int			wh[2];
//	char		*array;
	int			fd;

	wh[0] = param->width;
	wh[1] = param->height;
	(void)img;
	//array = mlx_get_data_addr(img, &f[0], &f[1], &f[2]);//modifier pour sdl2
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_header(fd, wh[0], wh[1]);
	//write_pixels(fd, wh[0], wh[1], array);
	close(fd);
}
