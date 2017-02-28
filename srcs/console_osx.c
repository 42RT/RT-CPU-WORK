/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 02:56:50 by rmorel            #+#    #+#             */
/*   Updated: 2014/12/21 02:56:51 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

char		translale_key(int keycode)
{
	static int	tbl[37] = {0, 11, 8, 2, 14, 3, 5, 4, 34, 38, 40, 37, 46, 45,
							31, 35, 12, 15, 1, 17, 32, 9, 13, 7, 16, 6, 29,
							18, 19, 20, 21, 23, 22, 26, 28, 25, SP_KEY};
	int			i;

	i = -1;
	while (++i < 26)
	{
		if (keycode == tbl[i])
			return ('a' + i);
	}
	--i;
	while (++i < 36)
	{
		if (keycode == tbl[i])
			return ('0' + i - 26);
	}
	if (keycode == SP_KEY)
		return (32);
	return (0);
}

void		write_console(int keycode, char *str)
{
	char	c[2];
	int		len;
	char	key;

	c[0] = 0;
	c[1] = 0;
	len = ft_strlen(str);
	if (len > 4 && len < 49)
		str[len - 4] = 0;
	key = translale_key(keycode);
	if (((key >= 'a' && key <= 'z')
		|| (key >= '0' && key <= '9') || key == ' ') && len < 49)
	{
		c[0] = key;
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
	if (translale_key(keycode) || keycode == ECHAP_KEY || keycode == SP_KEY)
		write_console(keycode, str);
	if (keycode == BACKSPACE_KEY)
		del_console(str);
	mlx_string_put(e->gfx->mlx, e->gfx->win, 4, e->gfx->buff[0]->height - 20,
		0x00FF3F, "Entrez un nom de fichier pour le screenshot: ");
	mlx_string_put(e->gfx->mlx, e->gfx->win, 450, e->gfx->buff[0]->height - 20,
		0x007FFF, str);
	if (keycode == RETURN_KEY)
	{
		expose_hook(e);
		if (str[0])
			save_image(e->gfx->screen, str, e->gfx->buff[e->gfx->act]);
		str[0] = 0;
		return (0);
	}
	return (keycode != ECHAP_KEY);
}*/
