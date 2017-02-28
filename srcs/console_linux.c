/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 02:56:50 by jrouilly          #+#    #+#             */
/*   Updated: 2015/10/18 13:03:41 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void		write_console(int keycode, char *str)
{
	char	c[2];
	int		len;

	c[0] = 0;
	c[1] = 0;
	len = ft_strlen(str);
	if (len > 4 && len < 49)
		str[len - 4] = 0;
	if (((keycode >= 'a' && keycode <= 'z')
		|| (keycode >= '0' && keycode <= '9') || keycode == SP_KEY) && len < 49)
	{
		c[0] = keycode;
		ft_strcat(str, c);
		ft_strcat(str, ".bmp");
	}
	if (keycode == ECHAP_KEY)
		str[0] = 0;
}

void		del_console(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 5)
		str[0] = 0;
	else if (len > 5)
	{
		str[len - 5] = 0;
		ft_strcat(str, ".bmp");
	}
}

/*int			rt_console(int keycode, t_env *e)
{
	static char	str[50] = "";
	void		*rec;

	rec = mlx_new_image(e->gfx->mlx, e->gfx->buff[0]->width, 16);
	mlx_put_image_to_window(e->gfx->mlx, e->gfx->win, rec, 0,
		e->gfx->buff[0]->height - 16);
	if ((keycode > 96 && keycode <= 122) || (keycode >= 48 && keycode <= 57)
		|| keycode == ECHAP_KEY || keycode == SP_KEY)
		write_console(keycode, str);
	if (keycode == BACKSPACE_KEY)
		del_console(str);
	mlx_string_put(e->gfx->mlx, e->gfx->win, 4, e->gfx->buff[0]->height - 3,
		0x00FF3F, "Entrer un nom de fichier pour le screenshot: ");
	mlx_string_put(e->gfx->mlx, e->gfx->win, 270, e->gfx->buff[0]->height - 3,
		0x007FFF, str);
	if (keycode == RETURN_KEY)
	{
		expose_hook(e);
		if (str[0])
			save_image(e->gfx->screen, str, e->gfx->buff[e->gfx->act]);
		return (0);
	}
	return (keycode != ECHAP_KEY);
}*/
